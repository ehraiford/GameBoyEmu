global unimplemented
unimplemented = 0

class Argument:
    def __init__(self, function: str, type: str):
        self.function = function
        self.type = type

    @classmethod
    def immediate_16(cls):
        return cls("reinterpret_cast<uint16_t*>(instr_ptr + 1)", "uint16_t*")
    @classmethod
    def immediate_8_unsigned(cls):
        return cls("instr_ptr + 1", "uint8_t*")
    @classmethod
    def immediate_8_signed(cls):
        return cls("instr_ptr + 1", "uint8_t*")
    @classmethod
    def r8(cls, val: int, operand_in_middle_of_bit: bool):
        if operand_in_middle_of_bit:
            val = (val & 0b00111000) >> 3
        else:
            val = val & 0b111
        if val == 0:
            return cls("cpu->get_b_pointer()", "uint8_t*")
        elif val == 1:
            return cls("cpu->get_c_pointer()", "uint8_t*")
        elif val == 2:
            return cls("cpu->get_d_pointer()", "uint8_t*")
        elif val == 3:
            return cls("cpu->get_e_pointer()", "uint8_t*")
        elif val == 4:
            return cls("cpu->get_h_pointer()", "uint8_t*")
        elif val == 5:
            return cls("cpu->get_l_pointer()", "uint8_t*")
        elif val == 6:
            return cls("cpu->todo()", "uint8_t*")
        elif val == 7:
            return cls("cpu->get_a_pointer()", "uint8_t*")  
    @classmethod    
    def r16(cls, val: int):
        val = (val & 0b00110000) >> 4
        if val == 0:
            return cls("cpu->get_bc_pointer()", "uint16_t*")
        elif val == 1:
            return cls("cpu->get_de_pointer()", "uint16_t*")
        elif val == 2:
            return cls("cpu->get_hl_pointer()", "uint16_t*")
        elif val == 3:
            return cls("cpu->get_sp_pointer()", "uint16_t*")

    @classmethod
    def r16stk(cls, val: int):
        val = (val & 0b00110000) >> 4
        if val == 0:
            return cls("cpu->get_bc_pointer()", "uint16_t*")
        elif val == 1:
            return cls("cpu->get_de_pointer()", "uint16_t*")
        elif val == 2:
            return cls("cpu->get_hl_pointer()", "uint16_t*")
        elif val == 3:
            return cls("cpu->get_af_pointer()", "uint16_t*")
    @classmethod       
    def r16mem(cls, val: int):
        val = (val & 0b00110000) >> 4
        if val == 0:
            return cls("cpu->get_bc_pointer()", "uint16_t*")
        elif val == 1:
            return cls("cpu->get_de_pointer()", "uint16_t*")  
        else:
            return cls("cpu->get_hl_pointer()", "uint16_t*")

    @classmethod
    def condition(cls, val: int):
        val = (val & 0b00011000) >> 3
        if val == 0:
            return cls("Condition::NZ", "Condition")
        elif val == 1:
            return cls("Condition::Z", "Condition")
        if val == 2:
            return cls("Condition::NC", "Condition")
        elif val == 3:
            return cls("Condition::C", "Condition")
    @classmethod
    def bit_index(cls, val: int):
        val = (val & 0b00111000) >> 3
        return cls(val, "uint8_t") 
class JumpTableEntry:

    def __init__(self, instruction_name: str, arguments: list[Argument]):
        self.instruction_name = instruction_name
        self.arguments = arguments

    def get_arguments_lambda(self) -> str:
        func = "[](Cpu* cpu, uint8_t* instr_ptr) -> void* "

        if len(self.arguments) == 0:
            func += "{ return nullptr; }"
        elif len(self.arguments) == 1 and (self.arguments[0].type == "uint8_t" or self.arguments[0].type == "Condition"):
            func += f"{{ return reinterpret_cast<void*>({self.arguments[0].function}); }}"
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


def hl_checks(byte: int):
    if byte == 0b00110100:
        return JumpTableEntry("increment_value_at_hl_address", [])
    elif byte == 0b00110101:
        return JumpTableEntry("decrement_value_at_hl_address", [])
    elif byte == 0b00110110:
        return JumpTableEntry("store_immediate_at_hl_address", [Argument.immediate_8_unsigned()])
    elif byte == 0b01110110:
        return JumpTableEntry("halt", [])
    elif byte & 0b11000111 == 0b01000110:
        return JumpTableEntry("load_from_hl_address", [Argument.r8(byte, True)])
    elif byte & 0b11111000 == 0b01110000:
        return JumpTableEntry("store_at_hl_address", [Argument.r8(byte, False)])
    elif byte == 0b10000110:
        return JumpTableEntry("add_value_at_hl_address_to_a", [])
    elif byte == 0b10001110:
        return JumpTableEntry("add_with_carry_from_hl_address_to_a", [])
    elif byte == 0b10010110:
        return JumpTableEntry("subtract_value_at_hl_address_from_a", [])
    elif byte == 0b10011110:
        return JumpTableEntry("subtract_with_carry_value_at_hl_address_from_a", [])
    elif byte == 0b10100110:
        return JumpTableEntry("and_a_with_value_at_hl_address", [])
    elif byte == 0b10101110:
        return JumpTableEntry("xor_a_with_value_at_hl_address", [])
    elif byte == 0b10110110:
        return JumpTableEntry("or_a_with_value_at_hl_address", [])
    elif byte == 0b10111110:
        return JumpTableEntry("compare_a_with_value_at_hl_address", [])

def hl_cb_checks(byte: int):
    if byte == 0b00000110:
        return JumpTableEntry("rotate_value_at_hl_address_left_with_carry", [])
    elif byte == 0b00001110:
        return JumpTableEntry("rotate_value_at_hl_address_right_with_carry", [])
    elif byte == 0b00010110:
        return JumpTableEntry("rotate_value_at_hl_address_left", [])
    elif byte == 0b00011110:
        return JumpTableEntry("rotate_value_at_hl_address_left", [])
    elif byte == 0b00100110:
        return JumpTableEntry("shift_value_at_hl_address_left_arithmetically", [])
    elif byte == 0b00101110:
        return JumpTableEntry("shift_value_at_hl_address_right_arithmetically", [])
    elif byte == 0b00110110:
        return JumpTableEntry("swap_register_nibbles", [])
    elif byte == 0b00111110:
        return JumpTableEntry("shift_value_at_hl_address_right_logically", [])
    elif byte & 0b11000111 == 0b01000110:
        return JumpTableEntry("set_zflag_if_value_at_hl_address_bit_not_set", [Argument.bit_index(byte)])
    elif byte & 0b11000111 == 0b10000110:
        return JumpTableEntry("clear_value_at_hl_address_bit", [Argument.bit_index(byte)])
    elif byte & 0b11000111 == 0b11000110:
        return JumpTableEntry("set_value_at_hl_address_bit", [Argument.bit_index(byte)])

def decode_byte(byte: int):
    hl_op = hl_checks(byte)
    if hl_op : return hl_op

    if byte == 0:
        return JumpTableEntry("nop", [])
    elif byte & 0b11001111 == 0b00000001:
        return JumpTableEntry("load_immediate_16bit", [Argument.r16(byte), Argument.immediate_16()])
    elif byte == 0b00100010:
        return JumpTableEntry("store_a_at_hl_address_increment", [Argument.r16mem(byte)])
    elif byte == 0b00110010:
        return JumpTableEntry("store_a_at_hl_address_decrement", [Argument.r16mem(byte)])
    elif byte & 0b11001111 == 0b00000010:
        return JumpTableEntry("store_a_at_register_address", [Argument.r16mem(byte)])
    elif byte == 0b00101010:
        return JumpTableEntry("load_a_from_hl_address_increment", [Argument.r16mem(byte)])
    elif byte == 0b00111010:
        return JumpTableEntry("load_a_from_hl_address_decrement", [Argument.r16mem(byte)])
    elif byte & 0b11001111 == 0b00001010:
        return JumpTableEntry("load_a_from_register_address", [Argument.r16mem(byte)])
    elif byte == 0b00001000:
        return JumpTableEntry("store_sp_at_immediate_address", [Argument.immediate_16()])
    elif byte & 0b11001111 == 0b00000011:
        return JumpTableEntry("increment_16bit_register", [Argument.r16(byte)])
    elif byte & 0b11001111 == 0b00001011:
        return JumpTableEntry("decrement_16bit_register", [Argument.r16(byte)])
    elif byte & 0b11001111 == 0b00001001:
        return JumpTableEntry("add_16bit_register_to_HL", [Argument.r16(byte)])
    elif byte & 0b11000111 == 0b00000100:
        return JumpTableEntry("increment_register", [Argument.r8(byte, True)])
    elif byte & 0b11000111 == 0b00000101:
        return JumpTableEntry("decrement_register", [Argument.r8(byte, True)])
    elif byte & 0b11000111 == 0b00000110:
        return JumpTableEntry("load_immediate_8bit", [Argument.r8(byte, True)])
    elif byte == 0b00000111:
        return JumpTableEntry("rotate_a_left_with_carry", [])
    elif byte == 0b00001111:
        return JumpTableEntry("rotate_a_right_with_carry", [])
    elif byte == 0b00010111:
        return JumpTableEntry("rotate_a_left", [])
    elif byte == 0b00011111:
        return JumpTableEntry("rotate_a_right", [])
    elif byte == 0b00100111:
        return JumpTableEntry("decimal_adjust_accumulator", [])
    elif byte == 0b00101111:
        return JumpTableEntry("invert_a", [])
    elif byte == 0b00110111:
        return JumpTableEntry("set_carry_flag", [])
    elif byte == 0b00111111:
        return JumpTableEntry("invert_carry_flag", [])
    elif byte == 0b00011000:
        return JumpTableEntry("jump_relative_to_immediate", [Argument.immediate_8_signed()])
    elif byte & 0b11100111 == 0b00100000:
        return JumpTableEntry("jump_relative_to_immediate_conditionally", [Argument.condition(byte), Argument.immediate_8_signed()])
    elif byte == 0b10000:
        return JumpTableEntry("stop", [])
    elif byte & 0b11000000 == 0b01000000:
        return JumpTableEntry("copy", [Argument.r8(byte, True), Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10000000:
        return JumpTableEntry("add_register_to_a", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10001000:
        return JumpTableEntry("add_with_carry_register_to_a", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10010000:
        return JumpTableEntry("subtract_register_from_a", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10011000:
        return JumpTableEntry("subtract_with_carry_register_from_a", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10100000:
        return JumpTableEntry("and_a_with_register", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10101000:
        return JumpTableEntry("xor_a_with_register", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10110000:
        return JumpTableEntry("or_a_with_register", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b10111000:
        return JumpTableEntry("compare_a_with_register", [Argument.r8(byte, False)])
    elif byte == 0b11000110:
        return JumpTableEntry("add_immediate_to_a", [Argument.immediate_8_unsigned()])
    elif byte == 0b11001110:
        return JumpTableEntry("add_with_carry_immediate_to_a", [Argument.immediate_8_unsigned()])
    elif byte == 0b11010110:
        return JumpTableEntry("subtract_immediate_from_a", [Argument.immediate_8_unsigned()])
    elif byte == 0b11011110:
        return JumpTableEntry("subtract_with_carry_immediate_from_a", [Argument.immediate_8_unsigned()])
    elif byte == 0b11100110:
        return JumpTableEntry("and_a_with_immediate", [Argument.immediate_8_unsigned()])
    elif byte == 0b11101110:
        return JumpTableEntry("xor_a_with_immediate", [Argument.immediate_8_unsigned()])
    elif byte == 0b11110110:
        return JumpTableEntry("or_a_with_immediate", [Argument.immediate_8_unsigned()])
    elif byte == 0b11111110:
        return JumpTableEntry("compare_a_with_immediate", [Argument.immediate_8_unsigned()])
    elif byte & 0b11100111 == 0b11000000:
        return JumpTableEntry("return_from_subroutine_conditionally", [Argument.condition(byte)])
    elif byte == 0b11001001:
        return JumpTableEntry("return_from_subroutine", [])
    elif byte == 0b11011001:
        return JumpTableEntry("return_from_interrupt_subroutine", [])
    elif byte & 0b11100111 == 0b11000010:
        return JumpTableEntry("jump_to_immediate_conditionally", [Argument.condition(byte), Argument.immediate_16()])
    elif byte == 0b11000011:
        return JumpTableEntry("jump_to_immediate", [Argument.immediate_16()])
    elif byte == 0b11101001:
        return JumpTableEntry("jump_to_value_at_hl_address", [])
    elif byte & 0b11100111 == 0b11000100:
        return JumpTableEntry("call_conditionally", [Argument.condition(byte), Argument.immediate_16()])
    elif byte == 0b11001101:
        return JumpTableEntry("call", [Argument.immediate_16()])
    elif byte & 0b11000111 == 0b11000111:
        return JumpTableEntry("call_vec", [Argument(f"reinterpret_cast<void*>({(byte & 0b00111000) >> 3})", "")])
    elif byte & 0b11001111 == 0b11000001:
        return JumpTableEntry("pop_stack_to_16bit_register", [Argument.r16stk(byte)])
    elif byte & 0b11001111 == 0b11000101:
        return JumpTableEntry("push_16bit_register_to_stack", [Argument.r16stk(byte)])
    elif byte == 0b11001011:
        return JumpTableEntry("nop", [])
    elif byte == 0b11100010:
        return JumpTableEntry("store_a_at_hardware_address_offset_by_c", [])
    elif byte == 0b11100000:
        return JumpTableEntry("store_a_at_immediate_hardware_address", [Argument.immediate_8_unsigned()])
    elif byte == 0b11101010:
        return JumpTableEntry("store_a_at_immediate_address", [Argument.immediate_16()])
    elif byte == 0b11110010:
        return JumpTableEntry("load_a_from_hardware_address_offset_by_c", [])
    elif byte == 0b11110000:
        return JumpTableEntry("load_a_from_immediate_hardware_address", [Argument.immediate_8_unsigned()])
    elif byte == 0b11111010:
        return JumpTableEntry("load_a_from_immediate_hardware_address", [])
    elif byte == 0b11101000:
        return JumpTableEntry("add_signed_immediate_to_sp", [Argument.immediate_8_signed()])
    elif byte == 0b11111000:
        return JumpTableEntry("load_hl_from_sp_plus_signed_immediate", [Argument.immediate_8_signed()])
    elif byte == 0b11111001:
        return JumpTableEntry("copy_hl_to_sp", [])
    elif byte == 0b11110011:
        return JumpTableEntry("disable_interrupts", [])
    elif byte == 0b11111011:
        return JumpTableEntry("enable_interrupts", [])
    elif any(byte == val for val in [0xD3, 0xDB, 0xDD, 0xE3, 0xE4, 0xEB, 0xEC, 0xED, 0xF4, 0xFC, 0xFD]):
        return JumpTableEntry("unsupported_op", [])
    else:
        print(f"What is missing: 0b{byte:08b}")

def decode_cb_byte(byte: int):
    hl_op = hl_cb_checks(byte)
    if hl_op : return hl_op

    if byte & 0b11111000 == 0b00000000:
        return JumpTableEntry("rotate_register_left_with_carry", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b00001000:
        return JumpTableEntry("rotate_register_right_with_carry", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b00010000:
        return JumpTableEntry("rotate_register_left", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b00011000:
        return JumpTableEntry("rotate_register_right", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b00100000:
        return JumpTableEntry("shift_register_left_arithmetically", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b00101000:
        return JumpTableEntry("shift_register_right_arithmetically", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b00110000:
        return JumpTableEntry("swap_register_nibbles", [Argument.r8(byte, False)])
    elif byte & 0b11111000 == 0b00111000:
        return JumpTableEntry("shift_register_right_logically", [Argument.r8(byte, False)])
    elif byte & 0b11000000 == 0b01000000:
        return JumpTableEntry("set_zflag_if_register_bit_not_set", [Argument.bit_index(byte), Argument.r8(byte, False)])
    elif byte & 0b11000000 == 0b10000000:
        return JumpTableEntry("clear_register_bit", [Argument.bit_index(byte), Argument.r8(byte, False)])
    elif byte & 0b11000000 == 0b11000000:
        return JumpTableEntry("set_register_bit", [Argument.bit_index(byte), Argument.r8(byte, False)])


with open("jump_table_py_output.txt", "w") as file:
    file.write("std::array<JumpTableEntry, 256> jump_table = {")
    for i in range(0, 256):
        file.write(decode_byte(i).to_string())
    file.write("\n};")

    file.write("std::array<JumpTableEntry, 256> jump_table_cb = {")
    for i in range(0,256):
        file.write(decode_cb_byte(i).to_string())
    file.write("\n};")

with open("jump_table_py_output.txt", "r") as file:
    for line in file.readlines():
        if "todo" in line:
            unimplemented += 1

print(f"{unimplemented} left unimplemented")