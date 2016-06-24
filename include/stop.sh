#!/bin/bash
# FILE: stop.sh
# DESC: Stop firewall and set policy ACCEPT
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos

if [ -z "${FW_DIR}" ];then

	# VARIABLES
	FW_DIR='/etc/firewall'
	FW_INCLUDE_DIR="${FW_DIR}/include"


	# INCLUDE VARIABLES
	echo "INCLUDE (${FW_INCLUDE_DIR}/variables.inc) ... "
	. ${FW_INCLUDE_DIR}/variables.inc

	# INCLUDE FUNCTIONS
	echo "INCLUDE (${FW_INCLUDE_DIR}/functions.inc) ... "
	. ${FW_INCLUDE_DIR}/functions.inc
fi

# FUNCTIONS AVAILABLE FROM HERE ;.)

# STOP FIREWALL
echo "STOP FIREWALL ... "

# BEEP 
f_beep 3

f_firewall_flush
f_firewall_policy ACCEPT

#__END__
