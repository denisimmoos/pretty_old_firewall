#!/bin/bash
# FILE: accept_tcp.inc
# DESC: ACCEPT TCP Rules
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos

echo "CONNECT ACCEPT RULES (${interface[$i]}) (tcp) ..."

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${accept_tcp}
do

	echo "	CONNECT ACCEPT RULE (tcp) (${each}) ..."

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
		-i ${interface[$i]} -p tcp \
		-s ${ip} --dport ${port} \
		-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
		-j TCPACCEPT \
		|| f_error "accept_tcp:1"
			
			case ${port} in 
				20|21|53)
	 				${IPTABLES} -A OUTPUT \
					-o ${interface[$i]} \
					-p tcp -d ${ip} --sport ${port} \
					-s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
					-j TCPACCEPT \
					|| f_error "accept_tcp:2"
				;;
				*)
	 				${IPTABLES} -A OUTPUT \
					-o ${interface[$i]} \
					-p tcp -d ${ip} --sport ${port} \
					-s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
					-m state --state ESTABLISHED -j TCPACCEPT \
					|| f_error "accept_tcp:3"
				;;
			esac
	else
			# TRICK
			port=${ip}

			# CHECK PORT
			f_check_port ${port}

			${IPTABLES} -A INPUT \
			-i ${interface[$i]} -p tcp \
			--dport ${port} \
			-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
			-j TCPACCEPT \
			|| f_error "accept_tcp:4"

			case ${port} in 
				20|21|53)

	 				${IPTABLES} -A OUTPUT \
					-o ${interface[$i]} \
					-p tcp --sport ${port} \
					-s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
					-j TCPACCEPT \
					|| f_error "accept_tcp:5"
				;;
				*)
		 			${IPTABLES} -A OUTPUT \
					-o ${interface[$i]} \
					-p tcp --sport ${port} \
					-s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
					-m state --state ESTABLISHED -j TCPACCEPT \
					|| f_error "accept_tcp:6"
				;;
			esac
	fi
	
done

# UNSET
unset each
unset ip
unset port

# RESTORE IFS
IFS=$OLDIFS

#__END__
