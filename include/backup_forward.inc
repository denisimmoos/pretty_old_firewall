#!/bin/bash
# FILE: backup_forward.inc
# DESC: FORWARD Backup Options
# DATE: 09.09.2006
# AUTOR: Denis Immoos


# PLACE XOR BACKUP DUMMY FORWARD CONFIGURATION

# IF FILE DOSN'T EXIST
if [ ! -f "${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}-${interface[$j]}" ];then
		
	echo "PLACE CLEAN CONFIGURATION FILE (${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}-${interface[$j]})"

	# Magic @@ Parse FORWARD
	#
	# INTERFACE: @INTERFACE_0@
	# IP ADRESS(@INTERFACE_0@): @IPADRESS_0@
	# SUBNET MASK(@INTERFACE_0@): @SUBNETMASK_0@
	# BROADCAST ADDRESS(@INTERFACE_0@): @BROADCASTADDRESS_0@
	# NETWORK ADDRESS(@INTERFACE_0@): @NETWORKADDRESS_0@
	# MAC ADDRESS(@INTERFACE_0@): @MACADDRESS_0@
	#
	# INTERFACE: @INTERFACE_1@
	# IP ADRESS(@INTERFACE_1@): @IPADRESS_1@
	# SUBNET MASK(@INTERFACE_1@): @SUBNETMASK_1@
	# BROADCAST ADDRESS(@INTERFACE_1@): @BROADCASTADDRESS_1@
	# NETWORK ADDRESS(@INTERFACE_1@): @NETWORKADDRESS_1@
	# MAC ADDRESS(@INTERFACE_1@): @MACADDRESS_1@
	
	echo "PARSE(${FW_INCLUDE_DIR}/dummy_forward.cat) ..."
	${CAT} ${FW_INCLUDE_DIR}/dummy_forward.cat | ${SED} \
	-e s#@INTERFACE_0@#${interface[$i]}#g \
	-e s#@IPADRESS_0@#${interface_ip[$i]}#g \
	-e s#@SUBNETMASK_0@#${interface_subnet_mask[$i]}#g \
	-e s#@BROADCASTADDRESS_0@#${interface_broadcast[$i]}#g \
	-e s#@NETWORKADDRESS_0@#${interface_network[$i]}#g \
	-e s#@MACADDRESS_0@#${interface_mac[$i]}#g \
	-e s#@INTERFACE_1@#${interface[$j]}#g \
	-e s#@IPADRESS_1@#${interface_ip[$j]}#g \
	-e s#@SUBNETMASK_1@#${interface_subnet_mask[$j]}#g \
	-e s#@BROADCASTADDRESS_1@#${interface_broadcast[$j]}#g \
	-e s#@NETWORKADDRESS_1@#${interface_network[$j]}#g \
	-e s#@MACADDRESS_1@#${interface_mac[$j]}#g \
	> ${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}-${interface[$j]}
	
fi
	
# BACKUP CONFIG
echo "BACKUP CONFIG(${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}-${interface[$j]}) ..."
${CAT} ${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}-${interface[$j]}  | ${GREP} -v "#" | ${GREP} -v "^$"  > ${FW_LOG_DIR}/${interface[$i]}-${interface[$j]}.${DATE}

# CREATE LINK
${LN} -sf ${FW_LOG_DIR}/${interface[$i]}-${interface[$j]}.${DATE} ${FW_LOG_DIR}/${interface[$i]}-${interface[$j]}

#__END__
