#!/bin/bash
# FILE: backup.sh
# DESC: Backup Firewall Script 
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

if [ -d "${FW_DIR}" ];then
	
  	echo "BACKUP FIREWALL SCRIPT (${FW_DIR} --> ${BACKUP_DIR}/${BACKUP}) ... "
	${TAR} czf ${BACKUP_DIR}/${BACKUP} ${FW_DIR} 2>${DEVNULL} 1>${DEVNULL} \
	|| f_warning "${TAR} czf ${BACKUP_DIR}/${BACKUP} ${FW_DIR} (ERROR)"
else
	f_warning "(${FW_DIR}) is not a directory ..."
fi

#__END__
