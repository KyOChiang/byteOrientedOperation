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

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = BANKED,
					 .operand3 = BANKED
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = ACCESS,
					 .operand3 = ACCESS
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_ACCESS_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = ACCESS,
					 .operand3 = BANKED
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_F(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = F,
					 .operand3 = F
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_W(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = W,
					 .operand3 = W
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_operand2_3_are_W_F(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x10,
					 .operand2 = W,
					 .operand3 = F
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
}

void test_rlncf_should_rotate_to_left_without_carry_with_valid_operand1_and_operand2_is_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	//OP3 should be empty if OP2 is written as ACCESS OR BANKED
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x57,
					 .operand2 = ACCESS,
					 .operand3 = -1
					};
					
	//Initialize FSR[code.operand1] with value 0xCB	- 1100 1011	
	//After rotate to left, become 1001 0111 - 97
	FSR[code.operand1] = 0xCB;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x97,FSR[WREG]);

}

void test_rlncf_should_rotate_to_left_without_carry_with_valid_operand1_and_operand2_is_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	//OP3 should be empty if OP2 is written as ACCESS OR BANKED
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x59,
					 .operand2 = BANKED,
					 .operand3 = -1
					};
					
	//Initialize FSR[code.operand1] with value 0xCB	- 1011 1100
	//After rotate to left, become 0111 1001 - 79
	FSR[code.operand1] = 0xBC;
	
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}

	TEST_ASSERT_EQUAL_HEX8(0x79,FSR[code.operand1]);

}

void test_rlncf_should_not_rotate_to_left_without_carry_and_throw_exception_on_invalid_BSR(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x22,
					 .operand2 = F,
					 .operand3 = BANKED
					};
					
	//Initialize FSR[code.operand1] with value 0xA4	- 1010 0101	
	FSR[code.operand1] = 0xA5;
	FSR[BSR] = 0x10;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xA5,FSR[code.operand1]);
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_to_selected_BSR_FileREG(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x22,
					 .operand2 = F,
					 .operand3 = BANKED
					};
					
	//Initialize FSR[code.operand1] with value 0x96	- 1001 0110
	//After rotate to left, become 0010 1101 - 2D
	FSR[code.operand1] = 0x96;
	FSR[BSR] = 0x01;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x2D,FSR[code.operand1+(FSR[BSR]<<8)]);
}

void test_rlncf_should_rotate_to_left_without_carry_and_store_to_WREG_without_consider_on_BSR(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = RLNCF, .name = "rlncf"},
					 .operand1 = 0x63,
					 .operand2 = W,
					 .operand3 = BANKED
					};
					
	//Initialize FSR[code.operand1] with value 0x69	- 0110 1001
	//After rotate to left, become 1101 0010 - D2
	FSR[code.operand1] = 0x69;
	FSR[BSR] = 0x03;
	Try{
		rlncf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_BSR, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0xD2,FSR[WREG]);
}