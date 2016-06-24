#!/bin/bash
# FILE: backup_connect.inc
# DESC: CONNECT Backup Options
# DATE: 09.09.2006
# AUTOR: Denis Immoos

# PLACE XOR BACKUP DUMMY CONNECT CONFIGURATION

# MKDIR FOR EACH 
if [ ! -d "${FW_INTERFACE_DIR}/${interface[$i]}" ];then
	${MKDIR} ${FW_INTERFACE_DIR}/${interface[$i]} 1>${DEVNULL} 2>${DEVNULL}
fi
	
# IF FILE DOSN'T EXIST
if [ ! -f "${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}" ];then
	
	echo "PLACE CLEAN CONFIGURATION FILE (${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}) ..."
	
	# Magic @@ Parse CONNECT
	#
	# INTERFACE: @INTERFACE@
	# IP ADRESS: @IPADRESS@
	# SUBNET MASK: @SUBNETMASK@
	# BROADCAST ADDRESS: @BROADCASTADDRESS@
	# NETWORK ADDRESS: @NETWORKADDRESS@
	# MAC ADDRESS: @MACADDRESS@

	echo "PARSE(${FW_INCLUDE_DIR}/dummy_connect.cat) ..."
	${CAT} ${FW_INCLUDE_DIR}/dummy_connect.cat | ${SED} \
	-e s#@INTERFACE@#${interface[$i]}#g \
	-e s#@IPADRESS@#${interface_ip[$i]}#g \
	-e s#@SUBNETMASK@#${interface_subnet_mask[$i]}#g \
	-e s#@BROADCASTADDRESS@#${interface_broadcast[$i]}#g \
	-e s#@NETWORKADDRESS@#${interface_network[$i]}#g \
	-e s#@MACADDRESS@#${interface_mac[$i]}#g \
	> ${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}
fi

# BACKUP CONFIG
echo "BACKUP CONFIG(${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}) ..."
${CAT} ${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}  | ${GREP} -v "#" | ${GREP} -v "^$"  > ${FW_LOG_DIR}/${interface[$i]}.${DATE}

# CREATE LINK
${LN} -sf ${FW_LOG_DIR}/${interface[$i]}.${DATE} ${FW_LOG_DIR}/${interface[$i]}

#__END__
