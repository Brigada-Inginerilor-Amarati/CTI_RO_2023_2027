project_new example1 -overwrite

set_global_assignment -name FAMILY MAX10
set_global_assignment -name DEVICE 10M50DAF484C7G 

set_global_assignment -name BDF_FILE example1.bdf
set_global_assignment -name VERILOG_FILE coffee_fsm.v
set_global_assignment -name SDC_FILE example1.sdc

set_global_assignment -name TOP_LEVEL_ENTITY coffee_fsm
set_location_assignment -to clk PIN_AH10

set_global_assignment -name 
set_global_assignment -name PIN_C10 -to credit5
set_global_assignment -name PIN_C11 -to credit10
set_global_assignment -name PIN_C12 -to cofee[0]
set_global_assignment -name PIN_A13 -to cofee[1]
set_global_assignment -name PIN_A8 -to exprr
set_global_assignment -name PIN_A9 -to expr_1
set_global_assignment -name PIN_A10 -to capp

load_package flow
execute_flow -compile

project_close
