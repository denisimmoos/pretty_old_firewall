#!/bin/bash
# FILE: help.sh
# DESC: Help script
# DATE: 08.09.2006
# AUTOR: Denis Immoos

if [ -z "${FW_DIR}" ];then
	
	# VARIABLES
	FW_DIR='/etc/firewall'
	FW_INCLUDE_DIR="${FW_DIR}/include"

	# INCLUDE VARIABLES
	. ${FW_INCLUDE_DIR}/variables.inc

fi

# HELP

# HERE DOCUMENT
${CAT} <<EOF

HELP: DENIS FIREWALL SCRIPT (${VERSION})

LICENSE: (${LICENSE})	

Not yet written ... :.)

EOF

#__END__
