global unimplemented
unimplemented = 0

class Argument:
    def __init__(self, function: str, type: str, disassembly: str):
        self.function = function
        self.type = type
        self.disassembly = disassembly

def remove_na_arguments(arguments: list[Argument]) -> list[Argument]:
    return_args = list[Argument]()
    for i in range(0, len(arguments)):
        if arguments[i].function != "N/A":
            return_args.append(arguments[i])
    return return_args

def immediate_16() -> Argument:
    function = "reinterpret_cast<uint16_t*>(instr_ptr + 1)"
    disassembly = f"std::format(\"${{:04x}}\", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]))"
    return Argument(function, "uint16_t*", disassembly)

def immediate_8_unsigned() -> Argument:
    function = "instr_ptr + 1"
    disassembly = f"std::format(\"${{:02x}}\", static_cast<int>(bytes[1]))"
    return Argument(function, "uint8_t*", disassembly)

def immediate_8_signed() -> Argument:
    function = "instr_ptr + 1"
    disassembly = f"std::format(\"${{:02x}}\", static_cast<int>(bytes[1]))"
    return Argument(function, "uint8_t*", disassembly)

def r8(val: int, operand_in_middle_of_bit: bool) -> Argument:
    if operand_in_middle_of_bit:
        val = (val & 0b00111000) >> 3
    else:
        val = val & 0b111
    if val == 0:
        return Argument("cpu->get_b_pointer()", "uint8_t*", "\"B\"")
    elif val == 1:
        return Argument("cpu->get_c_pointer()", "uint8_t*", "\"C\"")
    elif val == 2:
        return Argument("cpu->get_d_pointer()", "uint8_t*", "\"D\"")
    elif val == 3:
        return Argument("cpu->get_e_pointer()", "uint8_t*", "\"E\"")
    elif val == 4:
        return Argument("cpu->get_h_pointer()", "uint8_t*", "\"H\"")
    elif val == 5:
        return Argument("cpu->get_l_pointer()", "uint8_t*", "\"L\"")
    elif val == 7:
        return Argument("cpu->get_a_pointer()", "uint8_t*", "\"A\"") 
    else: return Argument("UNREACHABLE", "UNREACHABLE", "UNREACHABLE") 

def r16(val: int) -> Argument:
    val = (val & 0b00110000) >> 4
    if val == 0:
        return Argument("cpu->get_bc_pointer()", "uint16_t*", "\"BC\"")
    elif val == 1:
        return Argument("cpu->get_de_pointer()", "uint16_t*", "\"DE\"")
    elif val == 2:
        return Argument("cpu->get_hl_pointer()", "uint16_t*", "\"HL\"")
    elif val == 3:
        return Argument("cpu->get_sp_pointer()", "uint16_t*", "\"SP\"")

def r16stk(val: int) -> Argument:
    val = (val & 0b00110000) >> 4
    if val == 0:
        return Argument("cpu->get_bc_pointer()", "uint16_t*", "\"BC\"")
    elif val == 1:
        return Argument("cpu->get_de_pointer()", "uint16_t*", "\"DE\"")
    elif val == 2:
        return Argument("cpu->get_hl_pointer()", "uint16_t*", "\"HL\"")
    elif val == 3:
        return Argument("cpu->get_af_pointer()", "uint16_t*", "\"AF\"")
    
def r16mem(val: int) -> Argument :
    val = (val & 0b00110000) >> 4
    if val == 0:
        return Argument("cpu->get_bc_pointer()", "uint16_t*", "\"[BC]\"")
    elif val == 1:
        return Argument("cpu->get_de_pointer()", "uint16_t*", "\"[DE]\"")  
    else:
        return Argument("cpu->get_hl_pointer()", "uint16_t*", "\"[HL]\"")
    
def condition(val: int) -> Argument:
    val = (val & 0b00011000) >> 3
    if val == 0:
        return Argument("Condition::NZ", "Condition", "\"NZ\"")
    elif val == 1:
        return Argument("Condition::Z", "Condition", "\"Z\"")
    if val == 2:
        return Argument("Condition::NC", "Condition", "\"NC\"")
    elif val == 3:
        return Argument("Condition::C", "Condition", "\"C\"")

def bit_index(val: int) -> Argument:
    val = (val & 0b00111000) >> 3
    return Argument(val, "uint8_t", f"\"{val}\"") 

def hardware_address() -> Argument:
    function = "instr_ptr + 1"
    disassembly = f"std::format(\"[${{:02x}}]\", static_cast<int>(bytes[1]))"
    return Argument(function, "uint8_t*", disassembly)

def immediate_16_address() -> Argument:
    function = "reinterpret_cast<uint16_t*>(instr_ptr + 1)"
    disassembly = f"std::format(\"[${{:04x}}]\", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]))"
    return Argument(function, "uint16_t*", disassembly)

# The following functions are for operands used in opcodes mapped to functions where accessing said operand is part of the logic
# so they only exist for the disassembly view and the rest of the data is ignored
def sp() -> Argument:
    return Argument("N/A", "N/A", "\"SP\"")
# same as sp() above
def c_offset() -> Argument:
    return Argument("N/A", "N/A", "\"[C]\"")
def hl() -> Argument:
    return Argument("N/A", "N/A", "\"HL\"")
def hl_pointer() -> Argument:
    return Argument("N/A", "N/A", "\"[HL]\"")
def hli_pointer() -> Argument:
    return Argument("N/A", "N/A", "\"[HLI]\"")
def hld_pointer() -> Argument:
    return Argument("N/A", "N/A", "\"[HLD]\"")
def a() -> Argument:
    return Argument("N/A", "N/A", "\"A\"")
# this one, we need immediate, not signed so it's kinda like the above but not quite
def sp_plus_signed_immediate():
    function = "instr_ptr + 1"
    disassembly = f"std::format(\"SP + {{}}\", static_cast<int>(bytes[1]))"
    return Argument(function, "uint8_t*", disassembly)

class JumpTableEntry:

    def __init__(self, instruction_name: str, op_name: str, arguments: list[Argument]):
        self.instruction_name = instruction_name
        self.op_name = op_name
        self.arguments = arguments

    def get_arguments_lambda(self) -> str:
        func = "[](Cpu* cpu, uint8_t* instr_ptr) -> void* "
        arguments = remove_na_arguments(self.arguments)

        if len(arguments) == 0:
            func += "{ return nullptr; }"
        elif len(arguments) == 1 and (arguments[0].type == "uint8_t" or arguments[0].type == "Condition"):
            func += f"{{ return reinterpret_cast<void*>({arguments[0].function}); }}"
        elif len(arguments) == 1:
            func += f"{{ return {arguments[0].function}; }}"
        else:
            func += f"""{{
            auto* args = new std::pair<{arguments[0].type}, {arguments[1].type}>({arguments[0].function}, {arguments[1].function});
            return static_cast<void*>(args);
        }}"""
        return func

    def get_disassembly_lambda(self) -> str:
        func = "[](std::array<uint8_t, 3> bytes) -> const std::string {\n"
        if len(self.arguments) == 0:
            func += f"\t\t\treturn \"{self.op_name}\";\n"
        elif len(self.arguments) == 1:
            arg_is_string_literal = self.arguments[0].disassembly.find('(') == -1
            if arg_is_string_literal:
                arg_removed_quotes = self.arguments[0].disassembly.replace('"', '')
                func += f"\t\t\treturn \"{self.op_name} {arg_removed_quotes}\";\n"
            else:
                func += f"\t\t\tstd::string string = \"{self.op_name} \";\n"
                func += f"\t\t\tstring += {self.arguments[0].disassembly};\n"
                func += f"\t\t\treturn string;\n"  
        else:
            arg1_is_string_literal = self.arguments[0].disassembly.find('(') == -1
            arg2_is_string_literal = self.arguments[1].disassembly.find('(') == -1
            if arg1_is_string_literal and arg2_is_string_literal:
                arg1_removed_quotes = self.arguments[0].disassembly.replace('"', '')
                arg2_removed_quotes = self.arguments[1].disassembly.replace('"', '')
                func += f"\t\t\treturn \"{self.op_name} {arg1_removed_quotes},{arg2_removed_quotes}\";\n"
            else:
                func += f"\t\t\tstd::string string = \"{self.op_name} \";\n"
                func += f"\t\t\tstring += {self.arguments[0].disassembly};\n"
                func += f"\t\t\tstring += \",\";\n"
                func += f"\t\t\tstring += {self.arguments[1].disassembly};\n"
                func += f"\t\t\treturn string;\n"              
        func += "\t\t}"
        return func
    def to_string(self) -> str:
       return f"""
    JumpTableEntry {{
        &{self.instruction_name},
        {self.get_arguments_lambda()},
        {self.get_disassembly_lambda()}
    }},"""


def hl_checks(byte: int):
    if byte == 0b00110100:
        return JumpTableEntry("increment_value_at_hl_address", "INC", [hl_pointer()])
    elif byte == 0b00110101:
        return JumpTableEntry("decrement_value_at_hl_address", "DEC", [hl_pointer()])
    elif byte == 0b00110110:
        return JumpTableEntry("store_immediate_at_hl_address", "LD", [hl_pointer(), immediate_8_unsigned()])
    elif byte == 0b01110110:
        return JumpTableEntry("halt", "HALT", [])
    elif byte & 0b11000111 == 0b01000110:
        return JumpTableEntry("load_from_hl_address", "LD",  [r8(byte, True)])
    elif byte & 0b11111000 == 0b01110000:
        return JumpTableEntry("store_at_hl_address", "LD", [hl_pointer(), r8(byte, False)])
    elif byte == 0b10000110:
        return JumpTableEntry("add_value_at_hl_address_to_a", "ADD", [a(), hl_pointer()])
    elif byte == 0b10001110:
        return JumpTableEntry("add_with_carry_from_hl_address_to_a", "ADC", [a(), hl_pointer()])
    elif byte == 0b10010110:
        return JumpTableEntry("subtract_value_at_hl_address_from_a", "SUB", [a(), hl_pointer()])
    elif byte == 0b10011110:
        return JumpTableEntry("subtract_with_carry_value_at_hl_address_from_a", "SBC", [a(), hl_pointer()])
    elif byte == 0b10100110:
        return JumpTableEntry("and_a_with_value_at_hl_address", "AND", [a(), hl_pointer()])
    elif byte == 0b10101110:
        return JumpTableEntry("xor_a_with_value_at_hl_address", "XOR", [a(), hl_pointer()])
    elif byte == 0b10110110:
        return JumpTableEntry("or_a_with_value_at_hl_address", "OR", [a(), hl_pointer()])
    elif byte == 0b10111110:
        return JumpTableEntry("compare_a_with_value_at_hl_address", "CP", [a(), hl_pointer()])

def hl_cb_checks(byte: int):
    if byte == 0b00000110:
        return JumpTableEntry("rotate_value_at_hl_address_left_with_carry", "RLC", [hl_pointer()])
    elif byte == 0b00001110:
        return JumpTableEntry("rotate_value_at_hl_address_right_with_carry", "RRC", [hl_pointer()])
    elif byte == 0b00010110:
        return JumpTableEntry("rotate_value_at_hl_address_left", "RL", [hl_pointer()])
    elif byte == 0b00011110:
        return JumpTableEntry("rotate_value_at_hl_address_right", "RR", [hl_pointer()])
    elif byte == 0b00100110:
        return JumpTableEntry("shift_value_at_hl_address_left_arithmetically", "SLA", [hl_pointer()])
    elif byte == 0b00101110:
        return JumpTableEntry("shift_value_at_hl_address_right_arithmetically", "SRA", [hl_pointer()])
    elif byte == 0b00110110:
        return JumpTableEntry("swap_value_at_hl_address_nibbles", "SWAP", [hl()])
    elif byte == 0b00111110:
        return JumpTableEntry("shift_value_at_hl_address_right_logically", "SRL", [hl_pointer()])
    elif byte & 0b11000111 == 0b01000110:
        return JumpTableEntry("set_zflag_if_value_at_hl_address_bit_not_set", "BIT", [bit_index(byte), hl_pointer()])
    elif byte & 0b11000111 == 0b10000110:
        return JumpTableEntry("clear_value_at_hl_address_bit", "RES", [bit_index(byte), hl_pointer()])
    elif byte & 0b11000111 == 0b11000110:
        return JumpTableEntry("set_value_at_hl_address_bit", "SET", [bit_index(byte), hl_pointer()])

def decode_byte(byte: int):
    hl_op = hl_checks(byte)
    if hl_op : return hl_op

    if byte == 0:
        return JumpTableEntry("nop", "NOP", [])
    elif byte & 0b11001111 == 0b00000001:
        return JumpTableEntry("load_immediate_16bit", "LD", [r16(byte), immediate_16()])
    elif byte == 0b00100010:
        return JumpTableEntry("store_a_at_hl_address_increment", "LD", [hli_pointer(), a()])
    elif byte == 0b00110010:
        return JumpTableEntry("store_a_at_hl_address_decrement", "LD", [ hld_pointer(), a()])
    elif byte & 0b11001111 == 0b00000010:
        return JumpTableEntry("store_a_at_register_address", "LD", [r16mem(byte)])
    elif byte == 0b00101010:
        return JumpTableEntry("load_a_from_hl_address_increment", "LD", [a(), hli_pointer()])
    elif byte == 0b00111010:
        return JumpTableEntry("load_a_from_hl_address_decrement", "LD", [a(), hld_pointer()])
    elif byte & 0b11001111 == 0b00001010:
        return JumpTableEntry("load_a_from_register_address", "LD", [a(), r16mem(byte)])
    elif byte == 0b00001000:
        return JumpTableEntry("store_sp_at_immediate_address", "SP", [immediate_16()])
    elif byte & 0b11001111 == 0b00000011:
        return JumpTableEntry("increment_16bit_register", "INC", [r16(byte)])
    elif byte & 0b11001111 == 0b00001011:
        return JumpTableEntry("decrement_16bit_register", "DEC", [r16(byte)])
    elif byte & 0b11001111 == 0b00001001:
        return JumpTableEntry("add_16bit_register_to_HL", "ADD", [r16(byte)])
    elif byte & 0b11000111 == 0b00000100:
        return JumpTableEntry("increment_register", "INC", [r8(byte, True)])
    elif byte & 0b11000111 == 0b00000101:
        return JumpTableEntry("decrement_register", "DEC", [r8(byte, True)])
    elif byte & 0b11000111 == 0b00000110:
        return JumpTableEntry("load_immediate_8bit", "LD", [r8(byte, True), immediate_8_unsigned()])
    elif byte == 0b00000111:
        return JumpTableEntry("rotate_a_left_with_carry", "RLCA", [])
    elif byte == 0b00001111:
        return JumpTableEntry("rotate_a_right_with_carry", "RRCA", [])
    elif byte == 0b00010111:
        return JumpTableEntry("rotate_a_left", "RLA", [])
    elif byte == 0b00011111:
        return JumpTableEntry("rotate_a_right", "RRA", [])
    elif byte == 0b00100111:
        return JumpTableEntry("decimal_adjust_accumulator", "DAA", [])
    elif byte == 0b00101111:
        return JumpTableEntry("invert_a", "CPL", [])
    elif byte == 0b00110111:
        return JumpTableEntry("set_carry_flag", "SCF", [])
    elif byte == 0b00111111:
        return JumpTableEntry("invert_carry_flag", "CCF", [])
    elif byte == 0b00011000:
        return JumpTableEntry("jump_relative_to_immediate", "JR", [immediate_8_signed()])
    elif byte & 0b11100111 == 0b00100000:
        return JumpTableEntry("jump_relative_to_immediate_conditionally", "JR", [condition(byte), immediate_8_signed()])
    elif byte == 0b10000:
        return JumpTableEntry("stop", "STOP", [])
    elif byte & 0b11000000 == 0b01000000:
        return JumpTableEntry("copy", "LD", [r8(byte, True), r8(byte, False)])
    elif byte & 0b11111000 == 0b10000000:
        return JumpTableEntry("add_register_to_a", "ADD",  [r8(byte, False)])
    elif byte & 0b11111000 == 0b10001000:
        return JumpTableEntry("add_with_carry_register_to_a", "ADC", [r8(byte, False)])
    elif byte & 0b11111000 == 0b10010000:
        return JumpTableEntry("subtract_register_from_a", "SUB", [r8(byte, False)])
    elif byte & 0b11111000 == 0b10011000:
        return JumpTableEntry("subtract_with_carry_register_from_a", "SBC", [r8(byte, False)])
    elif byte & 0b11111000 == 0b10100000:
        return JumpTableEntry("and_a_with_register", "AND", [r8(byte, False)])
    elif byte & 0b11111000 == 0b10101000:
        return JumpTableEntry("xor_a_with_register", "XOR", [r8(byte, False)])
    elif byte & 0b11111000 == 0b10110000:
        return JumpTableEntry("or_a_with_register", "OR", [r8(byte, False)])
    elif byte & 0b11111000 == 0b10111000:
        return JumpTableEntry("compare_a_with_register", "CP", [r8(byte, False)])
    elif byte == 0b11000110:
        return JumpTableEntry("add_immediate_to_a", "ADD", [immediate_8_unsigned()])
    elif byte == 0b11001110:
        return JumpTableEntry("add_with_carry_immediate_to_a", "ADC", [immediate_8_unsigned()])
    elif byte == 0b11010110:
        return JumpTableEntry("subtract_immediate_from_a", "SUB", [immediate_8_unsigned()])
    elif byte == 0b11011110:
        return JumpTableEntry("subtract_with_carry_immediate_from_a", "SBC", [immediate_8_unsigned()])
    elif byte == 0b11100110:
        return JumpTableEntry("and_a_with_immediate", "AND", [immediate_8_unsigned()])
    elif byte == 0b11101110:
        return JumpTableEntry("xor_a_with_immediate", "XOR", [immediate_8_unsigned()])
    elif byte == 0b11110110:
        return JumpTableEntry("or_a_with_immediate", "OR", [immediate_8_unsigned()])
    elif byte == 0b11111110:
        return JumpTableEntry("compare_a_with_immediate", "CP", [immediate_8_unsigned()])
    elif byte & 0b11100111 == 0b11000000:
        return JumpTableEntry("return_from_subroutine_conditionally", "RET", [condition(byte)])
    elif byte == 0b11001001:
        return JumpTableEntry("return_from_subroutine", "RET", [])
    elif byte == 0b11011001:
        return JumpTableEntry("return_from_interrupt_subroutine", "RETI", [])
    elif byte & 0b11100111 == 0b11000010:
        return JumpTableEntry("jump_to_immediate_conditionally", "JP", [condition(byte), immediate_16()])
    elif byte == 0b11000011:
        return JumpTableEntry("jump_to_immediate", "JP", [immediate_16()])
    elif byte == 0b11101001:
        return JumpTableEntry("jump_to_value_at_hl_address", "JP", [hl_pointer()])
    elif byte & 0b11100111 == 0b11000100:
        return JumpTableEntry("call_conditionally", "CALL", [condition(byte), immediate_16()])
    elif byte == 0b11001101:
        return JumpTableEntry("call", "CALL", [immediate_16()])
    elif byte & 0b11000111 == 0b11000111:
        return JumpTableEntry("call_vec", "RST", [Argument(f"reinterpret_cast<void*>({(byte & 0b00111000) >> 3})", "uint8_t", f"std::format(\"{{:02x}}\", {(byte & 0b00111000) >> 3})"),])
    elif byte & 0b11001111 == 0b11000001:
        return JumpTableEntry("pop_stack_to_16bit_register", "POP", [r16stk(byte)])
    elif byte & 0b11001111 == 0b11000101:
        return JumpTableEntry("push_16bit_register_to_stack", "PUSH", [r16stk(byte)])
    elif byte == 0b11001011:
        return JumpTableEntry("nop", "CB INSTRUCTION", [])
    elif byte == 0b11100010:
        return JumpTableEntry("store_a_at_hardware_address_offset_by_c", "LDH", [c_offset(), a()])
    elif byte == 0b11100000:
        return JumpTableEntry("store_a_at_immediate_hardware_address", "LDH", [hardware_address(), a()])
    elif byte == 0b11101010:
        return JumpTableEntry("store_a_at_immediate_address", "LD", [immediate_16_address(), a()])
    elif byte == 0b11110010:
        return JumpTableEntry("load_a_from_hardware_address_offset_by_c", "LDH", [a(), c_offset()])
    elif byte == 0b11110000:
        return JumpTableEntry("load_a_from_immediate_hardware_address", "LDH", [a(), hardware_address()])
    elif byte == 0b11111010:
        return JumpTableEntry("load_a_from_immediate_address", "LD", [a(), immediate_16_address()])
    elif byte == 0b11101000:
        return JumpTableEntry("add_signed_immediate_to_sp", "ADD", [sp(), immediate_8_signed()])
    elif byte == 0b11111000:
        return JumpTableEntry("load_hl_from_sp_plus_signed_immediate", "LD", [hl(), sp_plus_signed_immediate()])
    elif byte == 0b11111001:
        return JumpTableEntry("copy_hl_to_sp", "LD", [sp(), hl()])
    elif byte == 0b11110011:
        return JumpTableEntry("disable_interrupts", "DI", [])
    elif byte == 0b11111011:
        return JumpTableEntry("enable_interrupts", "EI", [])
    elif any(byte == val for val in [0xD3, 0xDB, 0xDD, 0xE3, 0xE4, 0xEB, 0xEC, 0xED, 0xF4, 0xFC, 0xFD]):
        return JumpTableEntry("unsupported_op", "", [])
    else:
        print(f"What is missing: 0b{byte:08b}")

def decode_cb_byte(byte: int):
    hl_op = hl_cb_checks(byte)
    if hl_op : return hl_op

    if byte & 0b11111000 == 0b00000000:
        return JumpTableEntry("rotate_register_left_with_carry", "RLC", [r8(byte, False)])
    elif byte & 0b11111000 == 0b00001000:
        return JumpTableEntry("rotate_register_right_with_carry", "RRC", [r8(byte, False)])
    elif byte & 0b11111000 == 0b00010000:
        return JumpTableEntry("rotate_register_left", "RL", [r8(byte, False)])
    elif byte & 0b11111000 == 0b00011000:
        return JumpTableEntry("rotate_register_right", "RR", [r8(byte, False)])
    elif byte & 0b11111000 == 0b00100000:
        return JumpTableEntry("shift_register_left_arithmetically", "SLA", [r8(byte, False)])
    elif byte & 0b11111000 == 0b00101000:
        return JumpTableEntry("shift_register_right_arithmetically", "SRA", [r8(byte, False)])
    elif byte & 0b11111000 == 0b00110000:
        return JumpTableEntry("swap_register_nibbles", "SWAP", [r8(byte, False)])
    elif byte & 0b11111000 == 0b00111000:
        return JumpTableEntry("shift_register_right_logically", "SRA", [r8(byte, False)])
    elif byte & 0b11000000 == 0b01000000:
        return JumpTableEntry("set_zflag_if_register_bit_not_set", "BIT", [bit_index(byte), r8(byte, False)])
    elif byte & 0b11000000 == 0b10000000:
        return JumpTableEntry("clear_register_bit", "RES", [bit_index(byte), r8(byte, False)])
    elif byte & 0b11000000 == 0b11000000:
        return JumpTableEntry("set_register_bit", "SET", [bit_index(byte), r8(byte, False)])


with open("jump_table_py_output.txt", "w") as file:
    file.write("constexpr std::array<JumpTableEntry, 256> jump_table = {")
    for i in range(0, 256):
        file.write(decode_byte(i).to_string())
    file.write("\n};")

    file.write("constexpr std::array<JumpTableEntry, 256> jump_table_cb = {")
    for i in range(0,256):
        file.write(decode_cb_byte(i).to_string())
    file.write("\n};")

with open("jump_table_py_output.txt", "r") as file:
    for line in file.readlines():
        if "todo" in line:
            unimplemented += 1

print(f"{unimplemented} left unimplemented")