#!/bin/bash
# FILE: accept_icmp.inc
# DESC: accept_icmp Rules
# DATE: 08.09.2006
# AUTOR: Denis Immoos

# SAVE IFS
OLDIFS=$IFS
IFS=","

for each in ${accept_icmp}
do
  #CHECK IP
  f_check_ip ${each}

  echo "ACCEPT ICMP FOR (${each}) ON (${interface[$i]}) ... "

  # ACCEPT ICMP INPUT
  ${IPTABLES} -A INPUT \
  -i ${interface[$i]} \
  -s ${each} \
  -d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
  -p icmp -j ICMPINBOUND \
	|| f_error "accept_icmp:1"

done

# UNSET
unset each

# RESTORE IFS
IFS=$OLDIFS

#__END__
