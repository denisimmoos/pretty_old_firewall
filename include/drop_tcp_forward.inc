#!/bin/bash
# FILE: drop_tcp_forward.inc
# DESC: DROP tcp FORWARD Rules
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos
 
# DROP RULES TCP

echo "FORWARD DROP RULES (${interface[$i]} >> ${interface[$j]}) (tcp) ..."

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${drop_tcp}
do

  echo "	FORWARD DROP RULE (tcp) (${each}) ..."

  # EXAMPLE
  # 10.10.10.5>>80@192.100.30.2
  ip=`echo ${each} | ${AWK} -F">>" '{print $1}'`
  port=`echo ${each} | ${AWK} -F">>" '{print $2}' | ${AWK} -F "@" '{print $1}'`
  extip=`echo ${each} | ${AWK} -F">>" '{print $2}' | ${AWK} -F "@" '{print $2}'`

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
    --dport ${port} -j LDROP \
	|| f_error "drop_tcp_forward:1"
    
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
    --dport ${port} -j LDROP \
	|| f_error "drop_tcp_forward:2"

  else
    
    # CHECK
    f_check_ip ${ip}
    
    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${ip} \
    -p tcp --sport ${UNPRIVPORTS}  \
    -j LDROP \
	|| f_error "drop_tcp_forward:3"

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
