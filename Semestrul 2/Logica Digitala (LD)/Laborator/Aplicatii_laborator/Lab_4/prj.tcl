project_new example1 -overwrite

set_global_assignment -name FAMILY MAX10
set_global_assignment -name DEVICE 10M50DAF484C7G 

set_global_assignment -name BDF_FILE example1.bdf
set_global_assignment -name VERILOG_FILE maj_log.v
set_global_assignment -name SDC_FILE example1.sdc

set_global_assignment -name TOP_LEVEL_ENTITY rca
set_location_assignment -to clk PIN_AH10

set_location_assignment PIN_C10 -to a[0]  ;# SW[0]
set_location_assignment PIN_C11 -to a[1]  ;# SW[1]
set_location_assignment PIN_D12 -to a[2]  ;# SW[2]
set_location_assignment PIN_C12 -to a[3]  ;# SW[3]

set_location_assignment PIN_A12 -to b[0]  ;# SW[4]
set_location_assignment PIN_B12 -to b[1]  ;# SW[5]
set_location_assignment PIN_A13 -to b[2]  ;# SW[6]
set_location_assignment PIN_A14 -to b[3] ;# SW[7]

set_location_assignment PIN_B14 -to cin  ;# SW[8]

set_location_assignment PIN_A8  -to cout   ;# LED[0]
set_location_assignment PIN_A9  -to sum[0]  ;# LED[1]
set_location_assignment PIN_A10  -to sum[1] ;# LED[2]
set_location_assignment PIN_B10 -to sum[2]  ;# LED[3]
set_location_assignment PIN_D13 -to sum[3]  ;# LED[4]

load_package flow
execute_flow -compile

project_close
