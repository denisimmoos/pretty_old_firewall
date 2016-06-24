#!/bin/bash
# FILE: connect_link.inc
# DESC: create connect link 
# DATE: 05.04.2007
# AUTOR: Denis Immoos

# SAVE FOR LATER USE
echo ${interface_desc} > ${FW_LINK_DIR}/.${interface[$i]}.link

if [ -n "${interface_ip[$i]}" -a ! -L ${FW_LINK_DIR}/${interface_ip[$i]} ];then

	echo -n "CREATE DESCRIPTIVE LINK (${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]} -> ${FW_LINK_DIR}/${interface_ip[$i]}) ... "

	${LN} -sf ${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]} \
	${FW_LINK_DIR}/${interface_ip[$i]}

fi

# UNSET
unset interface_desc

#__END__
