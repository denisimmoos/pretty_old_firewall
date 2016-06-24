#!/bin/bash
# FILE: accept_icmp_forward.inc
# DESC: accept_icmp_forward Rules
# DATE: 08.09.2006
# AUTOR: Denis Immoos

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${accept_icmp}
do
  # EXAMPLE
  # 10.10.10.5>>192.100.30.2
  ip=`echo ${each} | ${AWK} -F">>" '{print $1}'`
  extip=`echo ${each} | ${AWK} -F">>" '{print $2}'`
  
  
	echo "ACCEPT FORWARD ICMP RULE (${each}) (${interface[$i]} >> ${interface[$j]})  ... "

  if [ -n "${ip}" -a -n "${extip}" ];then

    # CHECK
    f_check_ip ${ip}
    f_check_ip ${extip}

    # ACCEPT ICMP FORWARD
    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${ip} \
    -d ${extip} \
    -p icmp -j ACCEPT \
	|| f_error "accept_icmp_forward:1"

  else
  
    # TRICK
    extip=${ip}
    
    # CHECK
    f_check_ip ${extip}

    # ACCEPT ICMP FORWARD
    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${interface_network[$i]}/${interface_subnet_mask[$i]} \
    -d ${extip} \
    -p icmp -j ACCEPT \
	|| f_error "accept_icmp_forward:2"

  fi

done

# UNSET
unset each
unset ip
unset extip


# RESTORE IFS
IFS=$OLDIFS

#__END__
