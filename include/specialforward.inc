#!/bin/bash
# FILE: specialforward.inc
# DESC: specialforward Rules
# DATE: 12.09.2006
# AUTOR: Denis Immoos

# Port-Forwarding [inbound] (-->  Look also in PREROUTING chain)

# HTTP-Forwarding
# ${IPTABLES} -A FORWARD -i EXTERNAL_INTERFACE -p tcp \
# -d $HTTP --dport 80 -j ACCEPT

# Battlecom-Forwarding
# BATTLECOMIP="222.222.222.222"
# ${IPTABLES} -A FORWARD -p tcp --dport 2300:2400 \
# -i EXTERNAL_INTERFACE -d ${BATTLECOM} -j ACCEPT
#
# ${IPTABLES} -A FORWARD -p udp --dport 2300:2400 \
# -i EXTERNAL_INTERFACE -d ${BATTLECOMIP} -j ACCEPT
#
# ${IPTABLES} -A FORWARD -p tcp --dport 47624 \
# -i EXTERNAL_INTERFACE -d ${BATTLECOM} -j ACCEPT

#__END__
