import inspect

unimplemented = 0
class FunctionError(Exception):
    def __init__(self):
        frame = inspect.currentframe().f_back  # Get the caller's frame
        func_name = frame.f_code.co_name       # Get the function name
        args, _, _, values = inspect.getargvalues(frame)  # Get function arguments
        
        arg_str = ", ".join(f"{arg}={values[arg]!r}" for arg in args)  # Format arguments
        message = f"Error in {func_name}({arg_str})"
        
        super().__init__(message)

class Argument:
    def __init__(self, function: str, type: str):
        self.function = function
        self.type = type

    @classmethod
    def immediate_16(cls):
        return cls("instr_ptr + 1", "uint16_t*")
    @classmethod
    def immediate_8_unsigned(cls):
        return cls("reinterpret_cast<uint8_t*>(instr_ptr) + 2", "uint8_t*")
    @classmethod
    def immediate_8_signed(cls):
        return cls("reinterpret_cast<int8_t*>(instr_ptr) + 2", "int8_t*")

class JumpTableEntry:

    def __init__(self, instruction_name: str, arguments: list[Argument]):
        self.instruction_name = instruction_name
        self.arguments = arguments

    def get_arguments_lambda(self) -> str:
        func = "[](Cpu* cpu, uint16_t* instr_ptr) -> void* "

        if len(self.arguments) == 0:
            func += "{ return nullptr; }"
        elif len(self.arguments) == 1:
            func += f"{{ return {self.arguments[0].function}; }}"
        else:
            func += f"""{{
            auto* args = new std::pair<{self.arguments[0].type}, {self.arguments[1].type}>({self.arguments[0].function}, {self.arguments[1].function});
            return static_cast<void*>(args);
        }}"""
        return func

    def to_string(self) -> str:
       return f"""
    JumpTableEntry {{
        &{self.instruction_name},
        {self.get_arguments_lambda()}
    }},"""

def get_r8(val: int, operand_0: bool) -> Argument:

    if operand_0:
        #operand0 is always in bits 3:6
        val = (val & 0b00111000) >> 3
    else:
        #operand1 is always in bits 0:3
        val = val & 0b111
    if val == 0:
        return Argument("cpu->get_b_pointer()", "uint8_t*")
    elif val == 1:
        return Argument("cpu->get_c_pointer()", "uint8_t*")
    elif val == 2:
        return Argument("cpu->get_d_pointer()", "uint8_t*")
    elif val == 3:
        return Argument("cpu->get_e_pointer()", "uint8_t*")
    elif val == 4:
        return Argument("cpu->get_h_pointer()", "uint8_t*")
    elif val == 5:
        return Argument("cpu->get_l_pointer()", "uint8_t*")
    elif val == 6:
        return Argument("TODO", "TODO")
    elif val == 7:
        return Argument("cpu->get_a_pointer()", "uint8_t*")
    else:
        raise FunctionError()
    
def get_r16(val: int) -> Argument:
    val = (val & 0b00110000) >> 4
    if val == 0:
        return Argument("cpu->get_bc_pointer()", "uint16_t*")
    elif val == 1:
        return Argument("cpu->get_de_pointer()", "uint16_t*")
    elif val == 2:
        return Argument("cpu->get_hl_pointer()", "uint16_t*")
    elif val == 3:
        return Argument("cpu->get_sp_pointer()", "uint16_t*")
    else:
        raise FunctionError()
    
def get_r16stk(val: int) -> Argument:
    val = (val & 0b00110000) >> 4
    if val == 0:
        return Argument("cpu->get_bc_pointer()", "uint16_t*")
    elif val == 1:
        return Argument("cpu->get_de_pointer()", "uint16_t*")
    elif val == 2:
        return Argument("cpu->get_hl_pointer()", "uint16_t*")
    elif val == 3:
        return Argument("cpu->get_af_pointer()", "uint16_t*")
    else:
        raise FunctionError()
            
def get_r16_mem(val: int) -> Argument:
    val = (val & 0b00110000) >> 4
    if val == 0:
        return Argument("cpu->get_bc_pointer()", "uint16_t*")
    elif val == 1:
        return Argument("cpu->get_de_pointer()", "uint16_t*")  
    elif val == 2:
        return Argument("TODO", "TODO")
    elif val == 3:
        return Argument("TODO", "TODO")
    else:
        raise FunctionError()

def get_condition(val: int) -> str:
    if val == 0:
        return "Condition::NZ"
    elif val == 1:
        return "Condition::Z"
    if val == 2:
        return "Condition::NC"
    elif val == 3:
        return "Condition::C"
    else:
        raise FunctionError()
    

def decode_byte(byte: int):
    if byte == 0:
        return JumpTableEntry("nop", []).to_string()
    elif byte & 0b11001111 == 0b1:
        return JumpTableEntry("load_immediate_16bit", [get_r16(byte), Argument.immediate_16()]).to_string()
    elif byte & 0b11001111 == 0b10:
        return JumpTableEntry("store_a_at_register_address", [get_r16_mem(byte)]).to_string()
    elif byte & 0b11001111 == 0b1010:
        return JumpTableEntry("load_a_from_register_address", [get_r16_mem(byte)]).to_string()
    elif byte == 0b00001000:
        return JumpTableEntry("store_sp_at_immediate_address", [Argument.immediate_16()]).to_string()
    elif byte & 0b11001111 == 0b11:
        return JumpTableEntry("increment_16bit_register", [get_r16(byte)]).to_string()
    elif byte & 0b11001111 == 0b1011:
        return JumpTableEntry("decrement_16bit_register", [get_r16(byte)]).to_string()
    elif byte & 0b11001111 == 0b1001:
        return JumpTableEntry("add_16_bit_register_to_HL", [get_r16(byte)]).to_string()
    elif byte & 0b11000111 == 0b100:
        return JumpTableEntry("increment_register", [get_r8(byte, True)]).to_string()
    elif byte & 0b11000111 == 0b101:
        return JumpTableEntry("decrement_register", [get_r8(byte, True)]).to_string()
    elif byte & 0b11000111 == 0b110:
        return JumpTableEntry("load_immediate_8bit", [get_r8(byte, True)]).to_string()
    elif byte == 0b111:
        return JumpTableEntry("rotate_a_left_with_carry", []).to_string()
    elif byte == 0b1111:
        return JumpTableEntry("rotate_a_right_with_carry", []).to_string()
    elif byte == 0b10111:
        return JumpTableEntry("rotate_a_left", []).to_string()
    elif byte == 0b11111:
        return JumpTableEntry("rotate_a_right", []).to_string()
    elif byte == 0b100111:
        return JumpTableEntry("decimal_adjust_accumulator", []).to_string()
    elif byte == 0b101111:
        return JumpTableEntry("invert_a", []).to_string()
    elif byte == 0b110111:
        return JumpTableEntry("set_carry_flag", []).to_string()
    elif byte == 0b111111:
        return JumpTableEntry("invert_carry_flag", []).to_string()
    elif byte == 0b11000:
        return JumpTableEntry("jump_relative_to_immediate", [Argument.immediate_8_signed()]).to_string()
    elif byte & 0b111000111 == 0b100000:
        return JumpTableEntry("jump_relative_to_immediate_conditionally", [Argument.immediate_8_signed()]).to_string()
    elif byte == 0b10000:
        return JumpTableEntry("stop", []).to_string()
    elif byte & 0b11000000 == 0b01000000:
        return JumpTableEntry("copy", [get_r8(byte, True), get_r8(byte, False)]).to_string()
    elif byte == 0b1110110:
        return JumpTableEntry("halt", []).to_string()
    elif byte & 0b11111000 == 0b10000000:
        return JumpTableEntry("add_register_to_a", [get_r8(byte, True)]).to_string()
    elif byte & 0b11111000 == 0b10001000:
        return JumpTableEntry("add_with_carry_register_to_a", [get_r8(byte, True)]).to_string()
    else: 
        global unimplemented 
        unimplemented += 1
        return ""


with open("jump_table_py_output.txt", "w") as file:
    file.write("constexpr std::array<JumpTableEntry, 512> jump_table = {")
    for i in range(0, 256):
        file.write(decode_byte(i))
    file.write("\n};")
    print(f"{unimplemented} left unimplemented")