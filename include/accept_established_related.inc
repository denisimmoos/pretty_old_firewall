#!/bin/bash
# FILE: accept_established_related.inc
# DESC:accept_established_related RULES
# DATE: 08.09.2006
# AUTOR: Denis Immoos  	

echo "ACCEPT ESTABLISHED/RELATED RULES (${interface[$i]}) ..."

${IPTABLES} -A INPUT -i ${interface[$i]} \
-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
-m state --state ESTABLISHED -j ACCEPT \
|| f_error "accept_established_related:1"

${IPTABLES} -A INPUT -i ${interface[$i]} -p tcp \
-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
--dport ${UNPRIVPORTS} \
-m state --state RELATED -j TCPACCEPT \
|| f_error "accept_established_related:2"

${IPTABLES} -A INPUT -i ${interface[$i]} -p udp \
-d ${interface_ip[$i]}/${interface_subnet_mask[$i]} \
--dport ${ALLPORTS} \
-m state --state RELATED -j ACCEPT \
|| f_error "accept_established_related:3"

#__END__
