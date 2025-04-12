#include "Opcodes.h"
#include "../executors/Cpu.h"
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>

uint8_t OpCode::get_length() {
	return this->bytes;
};
uint8_t OpCode::get_cycles() {
	return this->cycles;
}
void NoArgCode::execute(Cpu* cpu, FuncArgs args) {
	(cpu->*opfunc)();
};
void OneU8Code::execute(Cpu* cpu, FuncArgs args) {
	uint8_t* arg = std::get<uint8_t*>(args);
	(cpu->*opfunc)(arg);
};
void TwoU8Code::execute(Cpu* cpu, FuncArgs args) {
	std::tuple<uint8_t*, uint8_t*> tuple_args = std::get<std::tuple<uint8_t*, uint8_t*>>(args);
	uint8_t* arg_0 = std::get<0>(tuple_args);
	uint8_t* arg_1 = std::get<1>(tuple_args);
	(cpu->*opfunc)(arg_0, arg_1);
};
void OneU16Code::execute(Cpu* cpu, FuncArgs args) {
	uint16_t* arg = std::get<uint16_t*>(args);
	(cpu->*opfunc)(arg);
};
void TwoU16Code::execute(Cpu* cpu, FuncArgs args) {
	std::tuple<uint16_t*, uint16_t*> tuple_args = std::get<std::tuple<uint16_t*, uint16_t*>>(args);
	uint16_t* arg_0 = std::get<0>(tuple_args);
	uint16_t* arg_1 = std::get<1>(tuple_args);
	(cpu->*opfunc)(arg_0, arg_1);
};
void ConU16Code::execute(Cpu* cpu, FuncArgs args) {
	std::tuple<Condition, uint16_t*> tuple_args = std::get<std::tuple<Condition, uint16_t*>>(args);
	Condition arg_0 = std::get<0>(tuple_args);
	uint16_t* arg_1 = std::get<1>(tuple_args);
	(cpu->*opfunc)(&arg_0, arg_1);
};
void OneI8Code::execute(Cpu* cpu, FuncArgs args) {
	int8_t* arg = std::get<int8_t*>(args);
	(cpu->*opfunc)(arg);
};
void ConI8Code::execute(Cpu* cpu, FuncArgs args) {
	std::tuple<Condition, int8_t*> tuple_args = std::get<std::tuple<Condition, int8_t*>>(args);
	Condition arg_0 = std::get<0>(tuple_args);
	int8_t* arg_1 = std::get<1>(tuple_args);
	(cpu->*opfunc)(&arg_0, arg_1);
};
void ConU8Code::execute(Cpu* cpu, FuncArgs args) {
	std::tuple<Condition, uint8_t*> tuple_args = std::get<std::tuple<Condition, uint8_t*>>(args);
	Condition arg_0 = std::get<0>(tuple_args);
	uint8_t* arg_1 = std::get<1>(tuple_args);
	(cpu->*opfunc)(&arg_0, arg_1);
};
void ConCode::execute(Cpu* cpu, FuncArgs args) {
	Condition arg = std::get<Condition>(args);
	(cpu->*opfunc)(&arg);
};