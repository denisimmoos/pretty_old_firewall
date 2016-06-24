#!/bin/bash
# FILE: functions.inc
# DESC: Include Script functions
# DATE: 07.09.2006
# AUTOR: Denis Immoos


#
# Firewall Flush
#

f_firewall_flush() {

  echo   "FLUSH ALL FIREWALL CHAINS ... "
  #Flush everything, start from scratch
  ${IPTABLES} -F
  ${IPTABLES} -F -t mangle
  ${IPTABLES} -F -t nat
  ${IPTABLES} -X
  ${IPTABLES} -X -t mangle
  ${IPTABLES} -X -t nat
}

#
# Firewall Policy
#

f_firewall_policy() {

  if [ "$1" = "ACCEPT" ];then
    echo   "SET DEFAULT POLICY TO (ACCEPT) ... "
    ${IPTABLES} -P INPUT ACCEPT
    ${IPTABLES} -P OUTPUT ACCEPT
    ${IPTABLES} -P FORWARD ACCEPT
  else
    #Set default policies to DROP
    echo "SET DEFAULT FIREWALL POLICY TO (DROP) ... "
    ${IPTABLES} -P INPUT DROP
    ${IPTABLES} -P OUTPUT DROP
    ${IPTABLES} -P FORWARD DROP
  fi
}

#
# Warning
#

f_warning() {
  f_beep 1
  echo -e "\nWARNING(${0}): ${1} !!!\n"
}

#
# Beep
#

f_beep() {
  BEEP="$1"
  
  if [ -z "${BEEP}" ];then	
    echo -en \\007 1>&2 
    BEEP="0"
  fi 
  
  # Beep Beep Beep ...
  for ((i=0; i < BEEP ; i++))
  do
    echo -en \\007 1>&2 
    sleep 1
  done
  
  unset BEEP
}

#
# Error
#
f_error() {
  f_beep 4
  f_firewall_flush
  f_firewall_policy DROP
  echo -e "\nERROR(${0}): $1 !!!\n"
  exit 1
}

#
# Include a file
#
f_include(){

  if [ -f "${1}" ];then
    echo "INCLUDE (${1}) ... "
    . ${1}
  else
    f_error "(${1}) is not a file"
  fi
}

#
# Load Module
#
f_load_module () {
  if ${MODPROBE} ${*} 1>${DEVNULL};then
    echo "LOAD MODULE(${1}) ..."
  else
    f_error "(${1}) not loaded"
  fi
}

#
#  Get Inerface Nr
#

#  Requires autoconf.inc

f_get_interface_nr()  {

	if echo ${interface[*]} | ${GREP}  ${1}  1>${DEVNULL} 2>${DEVNULL};then
			
	INTERFACES=$((${#interface[@]}-1))
	  
	  for ((f=0; f <= INTERFACES; f++))
	  do
		if [  "${interface[$f]}" == "${1}"  ];then
		  echo  "${f}"
		  break
		fi
	  done
	else
	  f_warning "(${1}) is not an network interface" 
	fi

}

#
#  Get Loopback Nr
#

#  Requires autoconf.inc

f_get_loopback_interface_nr() {
	
	INTERFACES=$((${#interface[@]}-1))
	
	for ((f=0; f <= INTERFACES; f++))
	do
	  # GUESS LOOPBACK
	  if [  -z "${interface_mac[$f]}" -a -z "${interface_broadcast[$f]}" ];then
		echo "${f}"
		break
	  fi
	done
}

#
# CHECK IP
#

f_check_ip() {
	
	check_ip[0]=`echo ${1} | ${AWK} -F "/" '{print $1}'`
	check_ip[1]=`echo ${1} | ${AWK} -F "/" '{print $2}'`
	
	IPA=$((${#check_ip[@]}-1))
		
	for ((f=0; f <= IPA; f++)) 
	do
		if [ -n "${check_ip[$f]}" ];then
			
			# SHORT IP MASK
			if ! echo ${check_ip[$f]} | ${EGREP} "^(0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|23|24|25|26|27|28|29|30|31|32)$" 2>${DEVNULL} 1>${DEVNULL}; then
				
				# IS IP ?
				if ! echo ${check_ip[$f]} | ${EGREP} "^([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])$" 2>${DEVNULL} 1>${DEVNULL}; then
					f_error "(${1}) is not an ip adress"
				fi
			fi
		fi
	done

	# SUPER SPECIAL CASE
	if echo ${check_ip[0]} | ${EGREP} "^(0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|23|24|25|26|27|28|29|30|31|32)$" 2>${DEVNULL} 1>${DEVNULL}; then
		f_error "(${1}) is not an ip adress"
	fi

	# UNSET
	unset check_ip
	unset IPA

}

#
# CHECK PORT
#

f_check_port() {

	check_port[0]=`echo ${1} | ${AWK} -F ":" '{print $1}'`
	check_port[1]=`echo ${1} | ${AWK} -F ":" '{print $2}'`
	
	PORTS=$((${#check_port[@]}-1))
	
	for ((f=0; f <= PORTS; f++)) 
	do
		if [ -n "${check_port[$f]}" ];then
		
			if ! ${EGREP} "^${check_port[$f]}$" ${FW_INCLUDE_DIR}/allports.egrep 2>${DEVNULL} 1>${DEVNULL}; then
				f_error "(${1}) (${check_port[$f]}) is not a port number"
			fi
		
		fi
	done
	
	if [ -n "${check_port[1]}" ];then
		if [ ${check_port[0]} -ge  ${check_port[1]} ];then
			f_error "(${1}) is not a valid port range (${check_port[0]} <! ${check_port[1]})"
		fi
	fi
	
	# UNSET
	unset check_port
	unset PORTS
	
}

#__END__
