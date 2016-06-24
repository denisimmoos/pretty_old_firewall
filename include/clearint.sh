#!/bin/bash
# FILE: clearint.sh
# DESC: Clear Firewall Interfaces 
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

if [ -d "${FW_INTERFACE_DIR}" ];then

  echo "CLEAR FIREWALL INTERFACES (${FW_INTERFACE_DIR}) ... "
  ${RM} -rf ${FW_INTERFACE_DIR}/*
  
else
  
  f_error "${FW_INTERFACE_DIR} is not a directory"
  
fi

#__END__
