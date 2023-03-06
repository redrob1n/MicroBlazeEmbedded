# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\redrob1n\workspace\MicroBlazeIP_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\redrob1n\workspace\MicroBlazeIP_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {MicroBlazeIP_wrapper}\
-hw {C:\Users\redrob1n\VivadoProjects\MicroBlazeIP\MicroBlazeIP_wrapper.xsa}\
-out {C:/Users/redrob1n/workspace}

platform write
domain create -name {standalone_microblaze_0} -display-name {standalone_microblaze_0} -os {standalone} -proc {microblaze_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {MicroBlazeIP_wrapper}
platform generate -quick
bsp reload
catch {bsp regenerate}
platform config -updatehw {C:/Users/redrob1n/VivadoProjects/MicroBlazeIP/MicroBlazeIP_wrapper.xsa}
platform clean
platform config -updatehw {C:/Users/redrob1n/VivadoProjects/MicroBlazeIP/MicroBlazeIP_wrapper.xsa}
platform config -updatehw {C:/Users/redrob1n/VivadoProjects/MicroBlazeIP/MicroBlazeIP_wrapper.xsa}
bsp reload
catch {bsp regenerate}
platform generate
