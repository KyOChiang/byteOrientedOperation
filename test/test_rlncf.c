#include "unity.h"
#include "CException.h"
#include "ByteCode.h"
#include "rlncf.h"

void setUp(){}
void tearDown(){}

void test_rlncf_should_rotate_to_left_without_carry_with_valid_operand1(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x23,
					 .operand2 = -1,
					 .operand3 = -1
					};
					
	//Initialize FSR[code.operand1] with value 0x45	- 0100 0101	
	//After rotate to left, become 1000 1010 - 8A
	FSR[code.operand1] = 0x45;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x8A,FSR[code.operand1]);

}

void test_rlncf_should_not_rotate_to_left_without_carry_with_invalid_operand1_negative1(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1
					};

	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
}

void test_rlncf_should_not_rotate_to_left_without_carry_with_invalid_operand1_0x100(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x100,
					 .operand2 = -1,
					 .operand3 = -1
					};
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_inside_filereg(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = F,
					 .operand3 = -1
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0100	
	//After rotate to left, become 0100 1001 - 49
	FSR[code.operand1] = 0xA4;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x49,FSR[code.operand1]);
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_inside_WREG(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = W,
					 .operand3 = -1
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	//After rotate to left, become 0100 1011 - 4B
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x4B,FSR[WREG]);
}