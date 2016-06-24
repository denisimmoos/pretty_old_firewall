#!/bin/bash
# FILE: drop_tcp.inc
# DESC: DROP tcp Rules
#
# DATE: 08.09.2006
# AUTOR: Denis Immoos
 
# DROP RULES TCP

echo "CONNECT DROP RULES (${interface[$i]}) (tcp) ..."

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${drop_tcp}
do

echo "	CONNECT DROP RULE (tcp) (${each}) ..."

	# EXAMPLE
	# 10.10.1.1@80
	# 10.12.3.5/255.255.255.0@8080:8090
	ip=`echo $each | ${AWK} -F"@" '{print $1}'`
	port=`echo $each | ${AWK} -F"@" '{print $2}'`
	
	# IF ${port} and ${ip} SET
	if [ -n "${port}" -a -n "${ip}" ];then

		#CHECK IP
		f_check_ip ${ip}

		#CHECK PORT
		f_check_port ${port}

		${IPTABLES} -A INPUT \
		-i ${interface[$i]} -p tcp \
		-s ${ip} --dport ${port} \
		-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
		-j LDROP \
		|| f_error "drop_tcp:1"

		${IPTABLES} -A OUTPUT \
		-o ${interface[$i]} -p tcp \
		-d ${ip} --sport ${port} \
		-s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
		-j LDROP \
		|| f_error "drop_tcp:2"

	else
		
		#CHECK IP
		f_check_ip ${ip}

		${IPTABLES} -A INPUT -i ${interface[$i]} -p tcp \
		-s ${ip} \
		-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
		-j LDROP \
		|| f_error "drop_tcp:3"

		${IPTABLES} -A OUTPUT \
		-o ${interface[$i]} -p tcp \
		-s ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
		-d ${ip} -j LDROP \
		|| f_error "drop_tcp:4"
	fi
done

# UNSET
unset each
unset ip
unset port

# RESTORE IFS
IFS=$OLDIFS

#__END__
