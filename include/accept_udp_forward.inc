#!/bin/bash
# FILE: accept_udp_forward.inc
# DESC: ACCEPT UDP FORWARD Rules
#
# DATE: 12.09.2006
# AUTOR: Denis Immoos

echo "FORWARD ACCEPT RULES (${interface[$i]} >> ${interface[$j]} ) (udp) ..."

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${accept_udp}
do

	echo "	FORWARD ACCEPT RULE (udp) (${each}) ..."

  # EXAMPLE
  # 10.10.10.5>>80@192.100.30.2
  ip=`echo ${each} | ${AWK} -F">>" '{print $1}'`
  port=`echo ${each} | ${AWK} -F">>" '{print $2}' | ${AWK} -F"@" '{print $1}'`
  extip=`echo ${each} | ${AWK} -F">>" '{print $2}' | ${AWK} -F"@" '{print $2}'`


  # IF PORT IP AND EXTIP
  if [ -n "${port}" -a -n "${ip}" -a -n "${extip}" ];then
  
    # CHECK
    f_check_ip ${ip}
    f_check_ip ${extip}
    f_check_port ${port}
  
    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${ip} \
    -p udp --sport ${ALLPORTS} \
    -d ${extip} \
    --dport ${port} \
    -j ACCEPT \
	|| f_error "accept_udp_forward:1"

  # IF PORT IP AND NO EXTIP
  elif [ -n "${port}" -a -n "${ip}" -a -z "${extip}" ];then
    
    # CHECK
    f_check_ip ${ip}
    f_check_port ${port}

    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${ip} \
    -p udp --sport ${ALLPORTS} \
    --dport ${port} -j ACCEPT \
	|| f_error "accept_udp_forward:2"

  else
    
    # TRICK
    port=${ip}

    # CHECK
    f_check_port ${port}

    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${interface_network[$i]}/${interface_subnet_mask[$i]} \
    -p udp --sport ${ALLPORTS}  \
    --dport ${port} \
    -j ACCEPT \
	|| f_error "accept_udp_forward:3"

  fi
  
done


# UNSET
unset each
unset ip
unset port
unset extip

# RESTORE IFS
IFS=$OLDIFS

#__END__
