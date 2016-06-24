#!/bin/bash
# FILE: drop_icmp_forward.inc
# DESC: drop_icmp_forward Rules
# DATE: 08.09.2006
# AUTOR: Denis Immoos
# BUGFIX: 05.04.2007
#         1,$s/ACCEPT/DROP/g
#         1,$s/INPUT/FORWARD/g

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${drop_icmp}
do
  	# EXAMPLE
  	# 10.10.10.5>>192.100.30.2
  	ip=`echo ${each} | ${AWK} -F">>" '{print $1}'`
  	extip=`echo ${each} | ${AWK} -F">>" '{print $2}'`
  
	echo "DROP FORWARD ICMP RULE (${each}) (${interface[$i]} >> ${interface[$j]})  ... "

  if [ -n "${ip}" -a -n "${extip}" ];then

    # CHECK
    f_check_ip ${ip}
    f_check_ip ${extip}

    # DROP ICMP FORWARD
    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${ip} \
    -d ${extip} \
    -p icmp -j DROP \
	|| f_error "drop_icmp_forward:1"

  else
  
    # CHECK
    f_check_ip ${ip}

    # DROP ICMP FORWARD
    ${IPTABLES} -A FORWARD \
    -i ${interface[$i]} \
    -o ${interface[$j]} \
    -s ${ip} \
    -p icmp -j DROP \
	|| f_error "drop_icmp_forward:2"

  fi

done

# UNSET
unset each
unset ip
unset extip


# RESTORE IFS
IFS=$OLDIFS

#__END__
