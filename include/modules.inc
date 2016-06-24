#!/bin/bash
# FILE: modules.inc
# DESC: Include Script modules
# DATE: 08.09.2006
# AUTOR: Denis Immoos

# Load ip_tables Kernel Module
# Basic Iptables Functions
f_load_module ip_tables

# Load iptable_filter Kernel Module
f_load_module iptable_filter

# Load iptable_mangle Kernel Module
f_load_module iptable_mangle

# Load ip_conntrack Kernel Module
# Connection Tracking
f_load_module ip_conntrack

# Load ip_conntrack_ftp Kernel Module
# Connection Tracking for FTP
f_load_module ip_conntrack_ftp

# Load ip_nat_ftp Kernel Module
# NAT for FTP
f_load_module ip_nat_ftp

# Ports for IRC-Connection-Tracking
# f_load_module "ip_conntrack_irc ports=${IRCPORTS}"
# f_load_module "ip_nat_irc ports=$IRCPORTS"

#__END__
