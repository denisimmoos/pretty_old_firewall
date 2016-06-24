#!/bin/bash
# FILE: accept_dhcp.inc
# DESC:accept_dhcp RULES
# DATE: 08.09.2006
# AUTOR: Denis Immoos


# DHCP SERVER

if [ "${accept_dhcp}" = "1"  ];then
  	
	echo "ACCEPT DHCP ON (${interface[$i]}) ... "
		
		# INPUT
		
		${IPTABLES} -A INPUT \
		-i ${interface[$i]} -p udp \
		--sport ${DHCPPORT67} \
		--dport ${DHCPPORT68} \
		-j ACCEPT \
		|| f_error "accept_dhcp:1" 

		${IPTABLES} -A INPUT \
		-i ${interface[$i]} -p udp \
	 	--sport ${DHCPPORT68} \
	 	--dport ${DHCPPORT68} \
	 	-j ACCEPT \
		|| f_error "accept_dhcp:2"

		${IPTABLES} -A INPUT \
		-i ${interface[$i]} -p udp \
	 	--dport ${DHCPPORT67} \
	 	--sport ${DHCPPORT68} \
	 	-j ACCEPT \
		|| f_error "accept_dhcp:3"

		${IPTABLES} -A INPUT \
		-i ${interface[$i]} -p udp \
	 	--dport ${DHCPPORT67} \
	 	--sport ${DHCPPORT67} \
	 	-j ACCEPT \
		|| f_error "accept_dhcp:4"

		# OUTPUT

		${IPTABLES} -A OUTPUT \
		-o ${interface[$i]} -p udp \
		--sport ${DHCPPORT67} \
		--dport ${DHCPPORT68} \
		-j ACCEPT \
		|| f_error "accept_dhcp:5"

		${IPTABLES} -A OUTPUT \
		-o ${interface[$i]} -p udp \
	 	--sport ${DHCPPORT67} \
	 	--dport ${DHCPPORT67} \
	 	-j ACCEPT \
		|| f_error "accept_dhcp:6"

		${IPTABLES} -A OUTPUT \
		-o ${interface[$i]} -p udp \
	 	--dport ${DHCPPORT67} \
	 	--sport ${DHCPPORT68} \
	 	-j ACCEPT \
		|| f_error "accept_dhcp:7"

		${IPTABLES} -A OUTPUT \
		-o ${interface[$i]} -p udp \
	 	--sport ${DHCPPORT68} \
	 	--dport ${DHCPPORT68} \
 		-j ACCEPT \
		|| f_error "accept_dhcp:8"
fi

#__END__
