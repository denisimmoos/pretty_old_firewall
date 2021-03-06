#!/bin/bash
# FILE: accept_udp.inc
# DESC: ACCEPT udp Rules
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos

echo "CONNECT ACCEPT RULES (${interface[$i]}) (udp) ..."

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${accept_udp}
do

	echo "	CONNECT ACCEPT RULE (udp) (${each}) ..."

	# EXAMPLE
	# 10.10.1.1@80
	# 10.12.3.5/255.255.255.0@8080:8090
	ip=`echo $each | ${AWK} -F"@" '{print $1}'`
	port=`echo $each | ${AWK} -F"@" '{print $2}'`
	
	# IF ${port} and ${ip} SET
	if [ -n "${port}" -a -n "${ip}" ];then

			#CHECK IP
			f_check_ip ${ip}

			# CHECK PORT
			f_check_port ${port}
  
			${IPTABLES} -A INPUT \
			-i ${interface[$i]} -p udp \
			-s ${ip} --dport ${port} \
			-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
			-j ACCEPT \
			|| f_error "accept_udp:1"

	 		${IPTABLES} -A OUTPUT \
			-o ${interface[$i]} \
			-p udp -d ${ip} --sport ${port} \
		        -s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
			-j ACCEPT \
			|| f_error "accept_udp:2"
	else
			# TRICK
			port=${ip}
			
			# CHECK PORT
			f_check_port ${port}
			
			${IPTABLES} -A INPUT \
			-i ${interface[$i]} -p udp \
			--dport ${port} \
			-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
			-j ACCEPT \
			|| f_error "accept_udp:3"

	 		${IPTABLES} -A OUTPUT \
			-o ${interface[$i]} \
			-p udp --sport ${port} \
			-s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
			-j ACCEPT \
			|| f_error "accept_udp:4"
	fi
	
done

# UNSET
unset each
unset ip
unset port

# RESTORE IFS
IFS=$OLDIFS

#__END__
