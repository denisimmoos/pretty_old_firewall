#!/bin/bash
# FILE: variables.inc
# DESC: variables
# DATE: 11.09.2006
# AUTOR: Denis Immoos  	

# Version n' License
VERSION="1.4.5.0"
LICENSE="GPL"

# Commands
IPTABLES=`type -P iptables`
MODPROBE=`type -P modprobe`
IFCONFIG=`type -P ifconfig`
AWK=`type -P awk`
SED=`type -P sed`
LN=`type -P ln`
EGREP=`type -P egrep`
GREP=`type -P grep`
ROUTE=`type -P route`
CAT=`type -P cat`
MKDIR=`type -P mkdir`
DATE=`/bin/date +%Y%m%d_%H_%M_%S`
RM=`type -P rm`

# BACKUP
TAR=`type -P tar`
BACKUP="firewall-${VERSION}-${DATE}.tar.gz"
BACKUP_DIR='/tmp'

# Directories n' Files
FW_DIR='/etc/firewall'
FW_INTERFACE_DIR="${FW_DIR}/interfaces"
FW_LINK_DIR="${FW_DIR}/links"
FW_INCLUDE_DIR="${FW_DIR}/include"
FW_LOG_DIR="${FW_DIR}/log"
FW_LOG_FILE="${FW_LOG_DIR}/firewall.log.${DATE}"

# Ports
ANYWHERE="0.0.0.0/0"
PRIVPORTS="0:1023"
UNPRIVPORTS="1024:65535"
ALLPORTS="0:65535"
BROADCAST="255.255.255.255"
DHCPPORT67="67"
DHCPPORT68="68"
TRACEROUTEPORTS="33434:33523"
IRCPORTS="6665,6666,6667,6668,6669,7000"

# ;.) NIRVANA
DEVNULL="/dev/null"

# CHAIN  VARIABLES
# used in chains.inc

# Overall Limit for TCP-SYN-Flood detection
TCPSYNLIMIT="20/s"

# Burst Limit for TCP-SYN-Flood detection
TCPSYNLIMITBURST="10"

# Overall Limit for Loggging in Logging-Chains
LOGLIMIT="2/s"

# Burst Limit for Logging in Logging-Chains
LOGLIMITBURST="10"

# Overall Limit for Ping-Flood-Detection
PINGLIMIT="5/s"

# Burst Limit for Ping-Flood-Detection
PINGLIMITBURST="10"

# LOG VARIABLES

# Look at IPREJECT in ipreject.inc and ipreject_chains.inc
IPREJECT="1"

# Log everything dropped
LOGDROP="1"

# Look at SILENTDROP in chains.inc
SILENTDROP="1"

# Look at SILENTREJECT in chains.inc
SILENTREJECT="1"

# Look at SILENTICMP in chains.inc
SILENTICMP="0"

# Look at SILENTBCAST in chains.inc
SILENTBCAST="1"

# Look at SPECIALPORT in chains.inc
SPECIALPORT="1"

#__END__
