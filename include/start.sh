#!/bin/bash
# FILE: start.sh
# DESC: Firewall start script
# DATE: 08.09.2006
# AUTOR: Denis Immoos

if [ -z "${FW_DIR}" ];then

	# VARIABLES
	FW_DIR='/etc/firewall'
	FW_INCLUDE_DIR="${FW_DIR}/include"

	# INCLUDE VARIABLES
	echo "INCLUDE (${FW_INCLUDE_DIR}/variables.inc) ... "
	. ${FW_INCLUDE_DIR}/variables.inc

	# INCLUDE FUNCTIONS
	echo "INCLUDE (${FW_INCLUDE_DIR}/functions.inc) ... "
	. ${FW_INCLUDE_DIR}/functions.inc

fi

# FUNCTIONS AVAILABLE FROM HERE ;.)

# START FIREWALL
echo "START FIREWALL ..."

# FLUSH ALL FIREWALL CHAINS
f_firewall_flush

# SET FIREWALL POLICY
f_firewall_policy DROP

# INCLUDE KERNELSETTINGS
f_include ${FW_INCLUDE_DIR}/kernel.inc

# INCLUDE MODULES
f_include ${FW_INCLUDE_DIR}/modules.inc

# INCLUDE AUTO CONFIGURATION
f_include ${FW_INCLUDE_DIR}/autoconf.inc

# INCLUDE CHAINS
f_include ${FW_INCLUDE_DIR}/chains.inc

# INCLUDE IPREJECT CHAINS+RULES
f_include ${FW_INCLUDE_DIR}/ipreject.inc

# INCLUDE PREROUTING
f_include ${FW_INCLUDE_DIR}/prerouting.inc

# POSTROUTING RULES
f_include ${FW_INCLUDE_DIR}/postrouting.inc

# SPECIAL FORWARD RULES
f_include ${FW_INCLUDE_DIR}/specialforward.inc

# INCLUDE GENERAL RULES
f_include ${FW_INCLUDE_DIR}/general_rules.inc

# INCLUDE LOOPBACK RULES
f_include ${FW_INCLUDE_DIR}/loopback_rules.inc

# COUNT INTERFACES
INTERFACES=$((${#interface[@]}-1))

# CONNECT RULES FOR EACH INTERFACE

for ((i=0; i <= INTERFACES; i++))
do
	# IF IT AIN'T A LOOPBACKDEVICES
	if [ -n "${interface_mac[$i]}" ];then
	
		# BACKUP CONFIGURATIONS
		f_include ${FW_INCLUDE_DIR}/backup_connect.inc
		
		# INCLUDE SPOOFING RULES
		f_include ${FW_INCLUDE_DIR}/spoofing_rules.inc
		
		# INCLUDE CONFIGURATION
		f_include ${FW_LOG_DIR}/${interface[$i]}.${DATE}
		
		# INCLUDE LINK CONFIGURATIONS
		f_include ${FW_INCLUDE_DIR}/connect_link.inc
	
		# INCLUDE NAT RULES
		f_include ${FW_INCLUDE_DIR}/nat.inc

		# INCLUDE DROP TCP RULES
		f_include ${FW_INCLUDE_DIR}/drop_tcp.inc
	
		# INCLUDE DROP UDP RULES
		f_include ${FW_INCLUDE_DIR}/drop_udp.inc
		
		# INCLUDE ACCEPT TCP RULES
		f_include ${FW_INCLUDE_DIR}/accept_tcp.inc
		
		# INCLUDE ACCEPT UDP RULES
		f_include ${FW_INCLUDE_DIR}/accept_udp.inc
		
		# INCLUDE DROP ICMP RULES
		f_include ${FW_INCLUDE_DIR}/drop_icmp.inc		
		
		# INCLUDE ACCEPT ICMP RULES
		f_include ${FW_INCLUDE_DIR}/accept_icmp.inc	

		# INCLUDE ACCEPT DHCP RULES
		f_include ${FW_INCLUDE_DIR}/accept_dhcp.inc	
		
		# INCLUDE ACCEPT ESTABLISHED RELATED RULES
		f_include ${FW_INCLUDE_DIR}/accept_established_related.inc	
	
		# INCLUDE ACCEPT ALLOUT RULES
		f_include ${FW_INCLUDE_DIR}/accept_allout.inc

		# FORWARD RULES
		
		for ((j=0; j <= INTERFACES; j++))
		do
			# IF THEY ARE NOT THE SAME
			if [ "${interface[$i]}" != "${interface[$j]}" ];then
			
				# IF THEY AIN'T LOOPBACKDEVICES
				if [ -n "${interface_mac[$i]}" -a -n "${interface_mac[$j]}" ];then
				
					# BACKUP CONFIGURATIONS
					f_include ${FW_INCLUDE_DIR}/backup_forward.inc
					
					# INCLUDE CONFIGURATION
					f_include ${FW_LOG_DIR}/${interface[$i]}-${interface[$j]}.${DATE}

					# INCLUDE FORWARD LINK CONFIGURATIONS
					f_include ${FW_INCLUDE_DIR}/forward_link.inc
					
					# INCLUDE DROP TCP RULES FORWARD
					f_include ${FW_INCLUDE_DIR}/drop_tcp_forward.inc
					
					# INCLUDE DROP UDP RULES FORWARD
					f_include ${FW_INCLUDE_DIR}/drop_udp_forward.inc
		
					# INCLUDE ACCEPT TCP RULES FORWARD
					f_include ${FW_INCLUDE_DIR}/accept_tcp_forward.inc
		
					# INCLUDE ACCEPT UDP RULES FORWARD
					f_include ${FW_INCLUDE_DIR}/accept_udp_forward.inc
		
					# INCLUDE DROP ICMP RULES
					f_include ${FW_INCLUDE_DIR}/drop_icmp_forward.inc		
		
					# INCLUDE ACCEPT ICMP RULES
					f_include ${FW_INCLUDE_DIR}/accept_icmp_forward.inc	
					
					# INCLUDE ACCEPT ESTABLISHED RELATED FORWARD RULES
					f_include ${FW_INCLUDE_DIR}/accept_established_related_forward.inc
					
				fi
			fi
		done
	
		# INCLUDE SILENTBCAST CHAINS
		f_include ${FW_INCLUDE_DIR}/silent_broadcast.inc
	fi
done

# INCLUDE LOG RULES
f_include ${FW_INCLUDE_DIR}/log_rules.inc

# BEEP
f_beep 1

#__END__
