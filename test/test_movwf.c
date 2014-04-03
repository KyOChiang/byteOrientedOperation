#include "unity.h"
#include "CException.h"
#include "ByteCode.h"
#include "movwf.h"

void setUp(){}
void tearDown(){}

void test_movwf_should_move_content_inside_WREG_to_selected_file_register(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x23,
					 .operand2 = -1,
					 .operand3 = -1
					};
					
	//Initialize WREG with value 0x45				
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1]);
}

void test_movwf_with_file_addr_more_than_0x7F_should_move_content_inside_WREG_to_BANKED_file_register(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x80,
					 .operand2 = -1,
					 .operand3 = -1
					};
					
	//Initialize WREG with value 0x45				
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND1, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x45,FSR[code.operand1+(0xF00)]);
}

void test_movwf_should_throw_an_exception_if_operand2_is_W(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x23,
					 .operand2 = W,
					 .operand3 = -1
					};
					
	//Initialize WREG with value 0x45	
	FSR[code.operand1] = 0x00;
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[code.operand1]);
}

void test_movwf_should_throw_an_exception_if_operand2_is_F(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x23,
					 .operand2 = F,
					 .operand3 = -1
					};
					
	//Initialize WREG with value 0x45	
	FSR[code.operand1] = 0x00;
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND2, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[code.operand1]);
}

void test_movwf_should_throw_an_exception_if_operand2_and_3_are_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x23,
					 .operand2 = BANKED,
					 .operand3 = BANKED
					};
					
	//Initialize WREG with value 0x45	
	FSR[code.operand1] = 0x00;
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[code.operand1]);
}

void test_movwf_should_throw_an_exception_if_operand2_and_3_are_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x23,
					 .operand2 = ACCESS,
					 .operand3 = ACCESS
					};
					
	//Initialize WREG with value 0x45	
	FSR[code.operand1] = 0x00;
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[code.operand1]);
}

void test_movwf_should_throw_an_exception_if_operand2_and_3_are_ACCESS_and_BANKED(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x23,
					 .operand2 = ACCESS,
					 .operand3 = BANKED
					};
					
	//Initialize WREG with value 0x45	
	FSR[code.operand1] = 0x00;
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[code.operand1]);
}

void test_movwf_should_throw_an_exception_if_operand2_and_3_are_BANKED_ACCESS(){
	CEXCEPTION_T errorStatus;
	//Test fixture
	
	Bytecode code = {.instruction = {.mnemonic = MOVWF, .name = "movwf"},
					 .operand1 = 0x23,
					 .operand2 = BANKED,
					 .operand3 = ACCESS
					};
					
	//Initialize WREG with value 0x45	
	FSR[code.operand1] = 0x00;
	FSR[WREG] = 0x45;
	
	Try{
		movwf(&code);
	}Catch(errorStatus){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERAND3, errorStatus);
	}
	
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[code.operand1]);
}
