setws .
app create -name app -hw ./xsa/[lindex $argv 0].xsa -os freertos10_xilinx -proc ps7_cortexa9_0 -template {Empty Application}
importsources -name app -path [lindex $argv 1] -soft-link
app config -add -name app include-path [lindex $argv 1]
app config -set -name app linker-script [lindex $argv 1]/lscript.ld
app build -name app
exit
