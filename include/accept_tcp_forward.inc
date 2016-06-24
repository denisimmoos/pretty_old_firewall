#!/bin/bash
# FILE: accept_tcp_forward.inc
# DESC: ACCEPT TCP FORWARD Rules
#
# DATE: 12.09.2006
# AUTOR: Denis Immoos

echo "FORWARD ACCEPT RULES (${interface[$i]} >> ${interface[$j]} ) (tcp) ..."

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${accept_tcp}
do

	echo "	FORWARD ACCEPT RULE (tcp) (${each}) ..."

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
    -p tcp --sport ${UNPRIVPORTS} \
    -d ${extip} \
    --dport ${port} \
    -j TCPACCEPT \
	|| f_error "accept_tcp_forward:1"

  # IF PORT IP AND NO EXTIP
  elif [ -n "${port}" -a -n "${ip}" -a -z "${extip}" ];then
    
    # CHECK
    f_check_ip ${ip}
    f_check_port ${port}

    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${ip} \
    -p tcp --sport ${UNPRIVPORTS} \
    --dport ${port} -j TCPACCEPT \
	|| f_error "accept_tcp_forward:2"

  else
    
    # TRICK
    port=${ip}

    # CHECK
    f_check_port ${port}

    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${interface_network[$i]}/${interface_subnet_mask[$i]} \
    -p tcp --sport ${UNPRIVPORTS}  \
    --dport ${port} \
    -j TCPACCEPT \
	|| f_error "accept_tcp_forward:3"

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
