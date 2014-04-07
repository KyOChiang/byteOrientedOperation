#include "unity.h"
#include "CException.h"
#include "ByteCode.h"
#include "subfwb.h"

void setUp(){}
void tearDown(){}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x23,
					 .operand2 = ACCESS,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x45;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x23,
					 .operand2 = BANKED,
					 .operand3 = BANKED,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x45;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_F(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x50,
					 .operand2 = F,
					 .operand3 = F,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x46;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x46,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_if_operand2_and_operand3_have_same_value_W(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x24,
					 .operand2 = W,
					 .operand3 = W,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x66;
	FSR[WREG] = 0x50;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x66,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}

void test_subfwb_should_throw_exception_for_invalid_BSR(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = SUBFWB, .name = "subfwb"},
					 .operand1 = 0x88,
					 .operand2 = ACCESS,
					 .operand3 = ACCESS,
					 .absoluteAddress = 0x05
					};
	FSR[code.operand1] = 0x45;
	FSR[WREG] = 0x50;
	FSR[BSR] = 0xAA;
	
	Try{
		subfwb(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
	TEST_ASSERT_EQUAL_HEX8(0x50,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x05,code.absoluteAddress);
}