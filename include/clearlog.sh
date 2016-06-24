#!/bin/bash
# FILE: clearlog.sh
# DESC: Clear Firewall Logs 
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

if [ -d "${FW_LOG_DIR}" ];then

  echo "CLEAR FIREWALL LOG (${FW_LOG_DIR}) ... "
  ${RM} -f ${FW_LOG_DIR}/*
  
else
  
  f_error "${FW_LOG_DIR} is not a directory"
  
  # FALSE
  exit 1
fi

#__END__
