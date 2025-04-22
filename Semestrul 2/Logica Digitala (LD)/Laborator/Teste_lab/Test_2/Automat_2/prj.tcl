project_new example1 -overwrite

set_global_assignment -name FAMILY MAX10
set_global_assignment -name DEVICE 10M50DAF484C7G

set_global_assignment -name BDF_FILE example1.bdf
set_global_assignment -name VERILOG_FILE automat.v
set_global_assignment -name SDC_FILE example1.sdc

set_global_assignment -name TOP_LEVEL_ENTITY automat


set_location_assignment -to clk PIN_F15; 
set_location_assignment -to rst PIN_B14;

set_location_assignment  PIN_C10 -to sel;
set_location_assignment  PIN_C11 -to rd;

set_location_assignment  PIN_A8 -to out[0];
set_location_assignment  PIN_A9 -to out[1];

set_location_assignment  PIN_A11 -to current_state[0];
set_location_assignment  PIN_B11 -to current_state[1];



load_package flow
execute_flow -compile

project_close