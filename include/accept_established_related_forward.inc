#!/bin/bash
# FILE: accept_established_related_forward.inc
# DESC:accept_established_related_forward RULES
# DATE: 12.09.2006
# AUTOR: Denis Immoos  	

echo "ACCEPT ESTABLISHED/RELATED FORWARD RULES (${interface[$i]} >> ${interface[$i]}) ..."

# Allow replies coming in
${IPTABLES} -A FORWARD \
-o ${interface[$j]} \
-m state --state ESTABLISHED -j ACCEPT \
|| f_error "accept_established_related_forward:1"

${IPTABLES} -A FORWARD \
-o ${interface[$j]} \
-p tcp --dport ${UNPRIVPORTS} \
-m state --state RELATED -j TCPACCEPT \
|| f_error "accept_established_related_forward:2"

${IPTABLES} -A FORWARD \
-o ${interface[$j]} \
-p udp --dport ${ALLPORTS} \
-m state --state RELATED -j ACCEPT \
|| f_error "accept_established_related_forward:3"

${IPTABLES} -A FORWARD \
-o ${interface[$j]} \
-p icmp -m state --state RELATED -j ACCEPT \
|| f_error "accept_established_related_forward:4"

#__END__
