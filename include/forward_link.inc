#!/bin/bash
# FILE: forward_link.inc
# DESC: create forward link 
# DATE: 05.04.2007
# AUTOR: Denis Immoos

# GET DESCRIPTION
if [ -f ${FW_LINK_DIR}/.${interface[$i]}.link -a -f ${FW_LINK_DIR}/.${interface[$j]}.link ];then

	interface_desc[$i]=`${CAT} ${FW_LINK_DIR}/.${interface[$i]}.link`
	interface_desc[$j]=`${CAT} ${FW_LINK_DIR}/.${interface[$j]}.link`

fi

if [ -n "${interface_desc[$i]}" -a -n "${interface_desc[$j]}" ];then

	echo -n "CREATE DESCRIPTIVE LINK (${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}-${interface[$j]} -> ${FW_LINK_DIR}/${interface_desc[$i]}-${interface_desc[$j]}) ... "

	${LN} -sf ${FW_INTERFACE_DIR}/${interface[$i]}/${interface[$i]}-${interface[$j]} \
	${FW_LINK_DIR}/${interface_desc[$i]}-${interface_desc[$j]}

fi

# UNSET
unset interface_desc

#__END__
