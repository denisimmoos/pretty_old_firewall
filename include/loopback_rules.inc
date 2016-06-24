#!/bin/bash
# FILE: loopback_rules.inc
# DESC: Loopback rules
# DATE: 09.09.2006
# AUTOR: Denis Immoos

# :.)
loopback_interface_nr=`f_get_loopback_interface_nr`

echo  "LOOPBACK INTERFACE RULES (\${interface[$loopback_interface_nr]}=${interface[$loopback_interface_nr]})  ... "

### INPUT ###
${IPTABLES} -A INPUT -i ${interface[$loopback_interface_nr]} -j ACCEPT \
|| f_error "loopback_rules:1"

# Kill connections to the local interface from the outside world 
# (--> Should be already catched by kernel/rp_filter)
  
${IPTABLES} -A INPUT \
-d ${interface_network[$loopback_interface_nr]}/${interface_subnet_mask[$loopback_interface_nr]} \
-j LREJECT \
|| f_error "loopback_rules:2"

### OUTPUT ###
${IPTABLES} -A OUTPUT -o ${interface[$loopback_interface_nr]} -j ACCEPT \
|| f_error "loopback_rules:3"

#__END__
