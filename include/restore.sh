#!/bin/bash
# FILE: restore.sh
# DESC: Restore Firewall config 
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


if [ -z "${1}" ];then
	echo
	echo "usage: ${0} restore FILE"
	echo
	exit 0
else
	restorefile=${2}
fi

if [ -z "${restorefile}" ];then
	echo
	echo "usage: ${0} restore FILE"
	echo
	exit 0
fi

# INCLUDE AUTOCONF
. ${FW_INCLUDE_DIR}/autoconf.inc

if [ -f "${restorefile}" ];then


	if ${EGREP} "^accept_tcp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^accept_udp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^drop_tcp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^drop_udp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^drop_icmp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^accept_icmp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^accept_dhcp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^nat.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} ;then

		echo "RESTORE CONNECT FILE (${restorefile}) ..."

		f_include ${restorefile}
		
		# GET INTERFACE NAME
		restore=`echo ${restorefile} | ${SED} -e s#.*/##g`
		int0=`echo ${restorefile} | ${SED} -e s#.*/##g | ${AWK} -F"." '{print $1}'` 
		nr=`f_get_interface_nr ${int0}`

		# RESTORE
		${CAT} ${FW_INCLUDE_DIR}/dummy_connect.cat | \
		${SED} \
		-e s#^accept_tcp.*#accept_tcp=\"${accept_tcp}\"#g \
		-e s#^drop_tcp.*#drop_tcp=\"${drop_tcp}\"#g \
		-e s#^nat.*#nat=\"${nat}\"#g \
		-e s#^drop_udp.*#drop_udp=\"${drop_udp}\"#g \
		-e s#^accept_udp.*#accept_udp=\"${accept_udp}\"#g \
		-e s#^drop_icmp.*#drop_icmp=\"${drop_icmp}\"#g \
		-e s#^accept_icmp.*#accept_icmp=\"${accept_icmp}\"#g \
		-e s#^accept_dhcp.*#accept_dhcp=\"${accept_dhcp}\"#g \
	        	-e s#@INTERFACE@#${interface[$nr]}#g \
        		-e s#@IPADRESS@#${interface_ip[$nr]}#g \
        		-e s#@SUBNETMASK@#${interface_subnet_mask[$nr]}#g \
        		-e s#@BROADCASTADDRESS@#${interface_broadcast[$nr]}#g \
       			-e s#@NETWORKADDRESS@#${interface_network[$nr]}#g \
       			-e s#@MACADDRESS@#${interface_mac[$nr]}#g \
					2>${DEVNULL} \
		> ${FW_LOG_DIR}/${int0}.restored || f_warning "(${FW_LOG_DIR}/${int0}.restored) could not parse file"

		echo "RESTORED TO (${FW_LOG_DIR}/${int0}.restored)"

	elif ${EGREP} "^accept_tcp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^accept_udp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^drop_tcp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^drop_udp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^drop_icmp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} && \
	${EGREP} "^accept_icmp.*" ${restorefile} 1>${DEVNULL} 2>${DEVNULL} ;then 
		
		echo "RESTORE FORWARD FILE (${restorefile}) ..."
		f_include ${restorefile}

		# GET INTERFACE NAMES
		int0=`echo ${restorefile} | ${SED} -e s#.*/##g | ${AWK} -F"." '{print $1}' | ${AWK} -F"-" '{print $1}'` 
		int1=`echo ${restorefile} | ${SED} -e s#.*/##g | ${AWK} -F"." '{print $1}' | ${AWK} -F"-" '{print $2}'` 
		# GET INTERFACE NUMBERS
		nr0=`f_get_interface_nr ${int0}`
		nr1=`f_get_interface_nr ${int1}`

		# RESTORE
		${CAT} ${FW_INCLUDE_DIR}/dummy_forward.cat | \
		${SED} \
		-e s#^drop_tcp.*#drop_tcp=\"${drop_tcp}\"#g \
		-e s#^accept_tcp.*#accept_tcp=\"${accept_tcp}\"#g \
		-e s#^drop_udp.*#drop_udp=\"${drop_udp}\"#g \
		-e s#^accept_udp.*#accept_udp=\"${accept_udp}\"#g \
		-e s#^accept_icmp.*#accept_icmp=\"${accept_icmp}\"#g \
		-e s#^accept_dhcp.*#accept_dhcp=\"${accept_dhcp}\"#g \
		        -e s#@INTERFACE_0@#${interface[$nr0]}#g \
        		-e s#@IPADRESS_0@#${interface_ip[$nr0]}#g \
        		-e s#@SUBNETMASK_0@#${interface_subnet_mask[$nr0]}#g \
        		-e s#@BROADCASTADDRESS_0@#${interface_broadcast[$nr0]}#g \
        		-e s#@NETWORKADDRESS_0@#${interface_network[$nr0]}#g \
        		-e s#@MACADDRESS_0@#${interface_mac[$nr0]}#g \
				-e s#@INTERFACE_1@#${interface[$nr1]}#g \
				-e s#@IPADRESS_1@#${interface_ip[$nr1]}#g \
				-e s#@SUBNETMASK_1@#${interface_subnet_mask[$nr1]}#g \
				-e s#@BROADCASTADDRESS_1@#${interface_broadcast[$nr1]}#g \
				-e s#@NETWORKADDRESS_1@#${interface_network[$nr1]}#g \
				-e s#@MACADDRESS_1@#${interface_mac[$nr1]}#g \
					2>${DEVNULL} \
		> ${FW_LOG_DIR}/${int0}-${int1}.restored \
		|| f_warning "(${FW_LOG_DIR}/${int0}-${int1}.restored) could not parse file"

		echo "RESTORED TO (${FW_LOG_DIR}/${int0}-${int1}.restored)"
	else
		f_warning "${restorefile} is not a backup file"
	fi
	
else
  
  f_warning "${restorefile} is not a file"
  
fi

#__END__
