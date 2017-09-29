
########## Tcl recorder starts at 10/05/16 10:51:09 ##########

set version "2.0"
set proj_dir "C:/Users/jeandres/Desktop"
cd $proj_dir

# Get directory paths
set pver $version
regsub -all {\.} $pver {_} pver
set lscfile "lsc_"
append lscfile $pver ".ini"
set lsvini_dir [lindex [array get env LSC_INI_PATH] 1]
set lsvini_path [file join $lsvini_dir $lscfile]
if {[catch {set fid [open $lsvini_path]} msg]} {
	 puts "File Open Error: $lsvini_path"
	 return false
} else {set data [read $fid]; close $fid }
foreach line [split $data '\n'] { 
	set lline [string tolower $line]
	set lline [string trim $lline]
	if {[string compare $lline "\[paths\]"] == 0} { set path 1; continue}
	if {$path && [regexp {^\[} $lline]} {set path 0; break}
	if {$path && [regexp {^bin} $lline]} {set cpld_bin $line; continue}
	if {$path && [regexp {^fpgapath} $lline]} {set fpga_dir $line; continue}
	if {$path && [regexp {^fpgabinpath} $lline]} {set fpga_bin $line}}

set cpld_bin [string range $cpld_bin [expr [string first "=" $cpld_bin]+1] end]
regsub -all "\"" $cpld_bin "" cpld_bin
set cpld_bin [file join $cpld_bin]
set install_dir [string range $cpld_bin 0 [expr [string first "ispcpld" $cpld_bin]-2]]
regsub -all "\"" $install_dir "" install_dir
set install_dir [file join $install_dir]
set fpga_dir [string range $fpga_dir [expr [string first "=" $fpga_dir]+1] end]
regsub -all "\"" $fpga_dir "" fpga_dir
set fpga_dir [file join $fpga_dir]
set fpga_bin [string range $fpga_bin [expr [string first "=" $fpga_bin]+1] end]
regsub -all "\"" $fpga_bin "" fpga_bin
set fpga_bin [file join $fpga_bin]

if {[string match "*$fpga_bin;*" $env(PATH)] == 0 } {
   set env(PATH) "$fpga_bin;$env(PATH)" }

if {[string match "*$cpld_bin;*" $env(PATH)] == 0 } {
   set env(PATH) "$cpld_bin;$env(PATH)" }

lappend auto_path [file join $install_dir "ispcpld" "tcltk" "lib" "ispwidget" "runproc"]
package require runcmd

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"adress_decoder_final.vhd\" -o \"adress_decoder_final.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 10:51:09 ###########


########## Tcl recorder starts at 10/05/16 10:51:20 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"adress_decoder_final.vhd\" -o \"adress_decoder_final.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 10:51:20 ###########


########## Tcl recorder starts at 10/05/16 10:51:26 ##########

# Commands to make the Process: 
# Create Fuse Map
if [catch {open address_decoder.cmd w} rspFile] {
	puts stderr "Cannot create response file address_decoder.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: adress_decoder_final.sty
PROJECT: address_decoder
WORKING_PATH: \"$proj_dir\"
MODULE: address_decoder
VHDL_FILE_LIST: adress_decoder_final.vhd
OUTPUT_FILE_NAME: address_decoder
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e address_decoder -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete address_decoder.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"address_decoder.edi\" -out \"address_decoder.bl0\" -err automake.err -log \"address_decoder.log\" -prj adress_decoder_final -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"address_decoder.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"address_decoder.bl1\" -o \"adress_decoder_final.bl2\" -omod address_decoder -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" adress_decoder_final.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" adress_decoder_final.bl3 -pla -o adress_decoder_final.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" adress_decoder_final.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" adress_decoder_final.tt3 -dev p16v8 -o adress_decoder_final.jed -ivec NoInput.tmv -rep adress_decoder_final.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/synsvf\" -exe \"$install_dir/ispvmsystem/ispufw\" -prj adress_decoder_final -if adress_decoder_final.jed -j2s -log adress_decoder_final.svl "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 10:51:26 ###########


########## Tcl recorder starts at 10/05/16 11:04:42 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"adress_decoder_final.vhd\" -o \"adress_decoder_final.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 11:04:42 ###########


########## Tcl recorder starts at 10/05/16 11:19:18 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"adress_decoder_final.vhd\" -o \"adress_decoder_final.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 11:19:18 ###########


########## Tcl recorder starts at 10/05/16 11:19:39 ##########

# Commands to make the Process: 
# Create Fuse Map
if [catch {open address_decoder.cmd w} rspFile] {
	puts stderr "Cannot create response file address_decoder.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: adress_decoder_final.sty
PROJECT: address_decoder
WORKING_PATH: \"$proj_dir\"
MODULE: address_decoder
VHDL_FILE_LIST: adress_decoder_final.vhd
OUTPUT_FILE_NAME: address_decoder
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e address_decoder -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete address_decoder.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"address_decoder.edi\" -out \"address_decoder.bl0\" -err automake.err -log \"address_decoder.log\" -prj adress_decoder_final -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"address_decoder.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"address_decoder.bl1\" -o \"adress_decoder_final.bl2\" -omod address_decoder -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" adress_decoder_final.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" adress_decoder_final.bl3 -pla -o adress_decoder_final.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" adress_decoder_final.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" adress_decoder_final.tt3 -dev p16v8 -o adress_decoder_final.jed -ivec NoInput.tmv -rep adress_decoder_final.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/synsvf\" -exe \"$install_dir/ispvmsystem/ispufw\" -prj adress_decoder_final -if adress_decoder_final.jed -j2s -log adress_decoder_final.svl "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 11:19:39 ###########


########## Tcl recorder starts at 10/05/16 11:30:46 ##########

# Commands to make the Process: 
# Hierarchy
if [runCmd "\"$cpld_bin/vhd2jhd\" \"adress_decoder_final.vhd\" -o \"adress_decoder_final.jhd\" -m \"$install_dir/ispcpld/generic/lib/vhd/location.map\" -p \"$install_dir/ispcpld/generic/lib\""] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 11:30:46 ###########


########## Tcl recorder starts at 10/05/16 11:31:31 ##########

# Commands to make the Process: 
# Create Fuse Map
if [catch {open address_decoder.cmd w} rspFile] {
	puts stderr "Cannot create response file address_decoder.cmd: $rspFile"
} else {
	puts $rspFile "STYFILENAME: adress_decoder_final.sty
PROJECT: address_decoder
WORKING_PATH: \"$proj_dir\"
MODULE: address_decoder
VHDL_FILE_LIST: adress_decoder_final.vhd
OUTPUT_FILE_NAME: address_decoder
SUFFIX_NAME: edi
"
	close $rspFile
}
if [runCmd "\"$cpld_bin/Synpwrap\" -e address_decoder -target ispGAL -pro "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
file delete address_decoder.cmd
if [runCmd "\"$cpld_bin/edif2blf\" -edf \"address_decoder.edi\" -out \"address_decoder.bl0\" -err automake.err -log \"address_decoder.log\" -prj adress_decoder_final -lib \"$install_dir/ispcpld/dat/mach.edn\" -cvt YES -net_Vcc VCC -net_GND GND -nbx -dse -tlw"] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" \"address_decoder.bl0\" -red bypin choose -collapse -pterms 8 -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblflink\" \"address_decoder.bl1\" -o \"adress_decoder_final.bl2\" -omod address_decoder -family -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/iblifopt\" adress_decoder_final.bl2 -red bypin choose -sweep -collapse all -pterms 8 -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/idiofft\" adress_decoder_final.bl3 -pla -o adress_decoder_final.tt2 -dev p16v8 -define N -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fit\" adress_decoder_final.tt2 -dev p16v8 -str -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/fuseasm\" adress_decoder_final.tt3 -dev p16v8 -o adress_decoder_final.jed -ivec NoInput.tmv -rep adress_decoder_final.rpt -doc brief -con ptblown -for brief -err automake.err "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}
if [runCmd "\"$cpld_bin/synsvf\" -exe \"$install_dir/ispvmsystem/ispufw\" -prj adress_decoder_final -if adress_decoder_final.jed -j2s -log adress_decoder_final.svl "] {
	return
} else {
	vwait done
	if [checkResult $done] {
		return
	}
}

########## Tcl recorder end at 10/05/16 11:31:31 ###########

