#!/bin/bash
# FILE: spoofing_rules.inc
# DESC: Firewall Chains
#
# DATE: 10.09.2006
# AUTOR: Denis Immoos

echo "SPOOFING RULES ... "

#IF IT AIN'T A LOOPBACK DEVICE
if [ -n "${interface_mac[$i]}"  ];then

	# SPOOFING
	for ((s=0; s <= INTERFACES; s++))
	do
		#IF IT AIN'T A LOOPBACK DEVICE
		if [ -n "${interface_mac[$s]}"  ];then
			
			# IF THEY ARE NOT THE SAME 
			if [  "${interface[$i]}" != "${interface[$s]}" ];then
				
				# LOG AND REJECT EVERYTHING WITH
				# SPOOFED SOURCE 
				${IPTABLES} -A INPUT -i ${interface[$i]} \
				-s ${interface_network[$s]}/${interface_subnet_mask[$s]} \
				-j LSPOOF
			fi
		fi
	done

fi

#__END__

