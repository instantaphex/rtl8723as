/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#define _RTL8723B_SRESET_C_

#include <rtl8723b_hal.h>


#ifdef DBG_CONFIG_ERROR_DETECT
void rtl8723b_sreset_xmit_status_check(_adapter *padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct sreset_priv *psrtpriv = &pHalData->srestpriv;

	unsigned long current_time;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	unsigned int diff_time;
	u32 txdma_status;

	txdma_status=rtw_read32(padapter, REG_TXDMA_STATUS);
	if( txdma_status !=0x00 && txdma_status !=0xeaeaeaea){
		DBG_871X("%s REG_TXDMA_STATUS:0x%08x\n", __FUNCTION__, txdma_status);
		rtw_hal_sreset_reset(padapter);
	}

	if (psrtpriv->dbg_trigger_point == SRESET_TGP_XMIT_STATUS) {
		psrtpriv->dbg_trigger_point = SRESET_TGP_NULL;
		rtw_hal_sreset_reset(padapter);
		return;
	}
}

void rtl8723b_sreset_linked_status_check(_adapter *padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct sreset_priv *psrtpriv = &pHalData->srestpriv;
#if 0
	u32 regc50,regc58,reg824,reg800;
	regc50 = rtw_read32(padapter,0xc50);
	regc58 = rtw_read32(padapter,0xc58);
	reg824 = rtw_read32(padapter,0x824);
	reg800 = rtw_read32(padapter,0x800);
	if(	((regc50&0xFFFFFF00)!= 0x69543400)||
		((regc58&0xFFFFFF00)!= 0x69543400)||
		(((reg824&0xFFFFFF00)!= 0x00390000)&&(((reg824&0xFFFFFF00)!= 0x80390000)))||
		( ((reg800&0xFFFFFF00)!= 0x03040000)&&((reg800&0xFFFFFF00)!= 0x83040000)))
	{
		DBG_8192C("%s regc50:0x%08x, regc58:0x%08x, reg824:0x%08x, reg800:0x%08x,\n", __FUNCTION__,
			regc50, regc58, reg824, reg800);
		rtw_hal_sreset_reset(padapter);
	}
#endif

	if (psrtpriv->dbg_trigger_point == SRESET_TGP_LINK_STATUS) {
		psrtpriv->dbg_trigger_point = SRESET_TGP_NULL;
		rtw_hal_sreset_reset(padapter);
		return;
	}
}

#endif

