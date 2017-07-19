#include "actu.h"
#include "am.h"
#include "cfgs.h"
#include "config.h"
#include "fs.h"
#include "kernel.h"
#include "main.h"
#include "mcu.h"
#include "misc.h"
#include "power.h"
#include "screenshot.h"
#include "system.h"
#include "utils.h"
#include "wifi.h"

void kernelMenu(void)
{	
	sftd_draw_text(font_m, ((400 - sftd_get_text_width(font_m, 12, "Kernel Menu")) / 2), 90, RGBA8(0, 0, 0, 255), 12, "Kernel Menu");

	sftd_draw_text(font_r, 20, 120, RGBA8(120, 118, 115, 255), 12, "Kernel version:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Kernel version:") + 3), 120, RGBA8(67, 72, 66, 255), 12, "%s", kernerlVersion);
	
	sftd_draw_text(font_r, 20, 136, RGBA8(120, 118, 115, 255), 12, "FIRM version:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "FIRM version:") + 3), 136, RGBA8(67, 72, 66, 255), 12, "%s", firmVersion);
	
	sftd_draw_text(font_r, 20, 152, RGBA8(120, 118, 115, 255), 12, "System version:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "System version:") + 3), 152, RGBA8(67, 72, 66, 255), 12, "%s", systemVersion);
	
	sftd_draw_text(font_r, 20, 168, RGBA8(120, 118, 115, 255), 12, "SDMC CID:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "SDMC CID:") + 3), 168, RGBA8(67, 72, 66, 255), 12, "%s", sdmcCID);

	sftd_draw_text(font_r, 20, 184, RGBA8(120, 118, 115, 255), 12, "NAND CID:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "NAND CID:") + 3), 184, RGBA8(67, 72, 66, 255), 12, "%s", nandCID);
	
	sftd_draw_text(font_r, 20, 200, RGBA8(120, 118, 115, 255), 12, "Device ID:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Device ID:") + 3), 200, RGBA8(67, 72, 66, 255), 12, "%lu", getDeviceId());
}

void systemMenu(void)
{
	sftd_draw_text(font_m, ((400 - sftd_get_text_width(font_m, 12, "System Menu")) / 2), 90, RGBA8(0, 0, 0, 255), 12, "System Menu");
	
	sftd_draw_text(font_r, 20, 120, RGBA8(120, 118, 115, 255), 12, "Model:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Model:") + 3), 120, RGBA8(67, 72, 66, 255), 12, "%s (%s)", getModel(), getRegion());
	
	sftd_draw_text(font_r, 20, 136, RGBA8(120, 118, 115, 255), 12, "Language:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Language:") + 3), 136, RGBA8(67, 72, 66, 255), 12, "%s", getLang());
	
	sftd_draw_text(font_r, 20, 152, RGBA8(120, 118, 115, 255), 12, "ECS Device ID:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "ECS Device ID:") + 3), 152, RGBA8(67, 72, 66, 255), 12, "%llu", getSoapId());
	
	sftd_draw_text(font_r, 20, 168, RGBA8(120, 118, 115, 255), 12, "Local friend code seed:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Local friend code seed:") + 3), 168, RGBA8(67, 72, 66, 255), 12, "%010llX", getLocalFriendCodeSeed());
	
	sftd_draw_text(font_r, 20, 184, RGBA8(120, 118, 115, 255), 12, "MAC Address:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "MAC Address:") + 3), 184, RGBA8(67, 72, 66, 255), 12, "%s", getMacAddress());
	
	sftd_draw_text(font_r, 20, 200, RGBA8(120, 118, 115, 255), 12, "Serial number:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Serial number:") + 3), 200, RGBA8(67, 72, 66, 255), 12, "%s", getSerialNum());
	
	sftd_draw_text(font_r, 20, 216, RGBA8(120, 118, 115, 255), 12, "Screen type:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Screen type:") + 3), 216, RGBA8(67, 72, 66, 255), 12, "%s", getScreenType());
}

void batteryMenu(void)
{
	u8 batteryPercent = 0, batteryVolt = 0, mcuFwMajor = 0, mcuFwMinor = 0;
	bool isConnected = false;
	
	sftd_draw_text(font_m, ((400 - sftd_get_text_width(font_m, 12, "Battery Menu")) / 2), 90, RGBA8(0, 0, 0, 255), 12, "Battery Menu");
	
	mcuGetBatteryLevel(&batteryPercent);
	mcuGetBatteryVoltage(&batteryVolt);
	
	sftd_draw_text(font_r, 20, 120, RGBA8(120, 118, 115, 255), 12, "Battery percentage:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Battery percentage:") + 3), 120, RGBA8(67, 72, 66, 255), 12, "%3d%%", batteryPercent);
	
	sftd_draw_text(font_r, 20, 136, RGBA8(120, 118, 115, 255), 12, "Battery status:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Battery status:") + 3), 136, RGBA8(67, 72, 66, 255), 12, "%s", batteryStatus());
	
	sftd_draw_text(font_r, 20, 152, RGBA8(120, 118, 115, 255), 12, "Battery voltage:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Battery voltage:") + 3), 152, RGBA8(67, 72, 66, 255), 12, "%d (%.1f V)", batteryVolt, 5.0 * ((double)batteryVolt / 256.0));
	
	PTMU_GetAdapterState(&isConnected);
	sftd_draw_text(font_r, 20, 168, RGBA8(120, 118, 115, 255), 12, "Adapter state:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Adapter state:") + 3), 168, RGBA8(67, 72, 66, 255), 12, "%s", isConnected? "connected" : "disconnected");
	
	GetMcuFwVerHigh(&mcuFwMajor);
	GetMcuFwVerLow(&mcuFwMinor);
	//if (CFG_UNITINFO == 0)
	sftd_draw_text(font_r, 20, 184, RGBA8(120, 118, 115, 255), 12, "MCU firmware:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "MCU firmware:") + 3), 184, RGBA8(67, 72, 66, 255), 12, "%u.%u", (mcuFwMajor - 16), mcuFwMinor);
}

void NNIDInfoMenu(void)
{	
	u32 principalID = 0;
	char name[0x16];
	
	AccountDataBlock accountDataBlock;
	ACTU_GetAccountDataBlock((u8*)&accountDataBlock, 0xA0, 0x11);

	sftd_draw_text(font_m, ((400 - sftd_get_text_width(font_m, 12, "NNID Menu")) / 2), 90, RGBA8(0, 0, 0, 255), 12, "NNID Menu");
	
	// getNNIDInfo(0x11, 0x8), getNNIDInfo(0x11, 0x1C), getNNIDInfo(0x11, 0x15) are all the same.
	sftd_draw_text(font_r, 20, 120, RGBA8(120, 118, 115, 255), 12, "NNID:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "NNID:") + 3), 120, RGBA8(67, 72, 66, 255), 12, "%s", getNNIDInfo(0x11, 0x8));

	utf2ascii(name, accountDataBlock.miiName);
	sftd_draw_text(font_r, 20, 136, RGBA8(120, 118, 115, 255), 12, "Mii name:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Mii name:") + 3), 136, RGBA8(67, 72, 66, 255), 12, "%s", name);
	
	ACTU_GetAccountDataBlock(&principalID, 0x4, 0xC);
	sftd_draw_text(font_r, 20, 152, RGBA8(120, 118, 115, 255), 12, "Principal ID:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Principal ID:") + 3), 152, RGBA8(67, 72, 66, 255), 12, "%u", principalID);
	
	sftd_draw_text(font_r, 20, 168, RGBA8(120, 118, 115, 255), 12, "Persistent ID:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Persistent ID:") + 3), 168, RGBA8(67, 72, 66, 255), 12, "%u", accountDataBlock.persistentID);
	
	sftd_draw_text(font_r, 20, 184, RGBA8(120, 118, 115, 255), 12, "Transferable ID Base:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Transferable ID Base:") + 3), 184, RGBA8(67, 72, 66, 255), 12, "%llu", accountDataBlock.transferableID);
	
	sftd_draw_text(font_r, 20, 200, RGBA8(120, 118, 115, 255), 12, "Country:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Country:") + 3), 200, RGBA8(67, 72, 66, 255), 12, "%s", getNNIDInfo(0x3, 0xB));
	
	sftd_draw_text(font_r, 20, 216, RGBA8(120, 118, 115, 255), 12, "Time Zone:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Time Zone:") + 3), 216, RGBA8(67, 72, 66, 255), 12, "%s", getNNIDInfo(0x41, 0x1E));
	
	/*sftd_draw_text(font_r, 20, 184, RGBA8(120, 118, 115, 255), 12, "Mii url:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Mii url:") + 3), 184, RGBA8(67, 72, 66, 255), 12, "%.54s", getNNIDInfo(0x101, 0x25));
	sftd_draw_textf(font_r, 20, 195, RGBA8(67, 72, 66, 255), 12, "%s", getNNIDInfo(0x101, 0x25) + + strlen(getNNIDInfo(0x101, 0x25)) - 12);*/
}

void configInfoMenu(void)
{	
	sftd_draw_text(font_m, ((400 - sftd_get_text_width(font_m, 12, "Config Menu")) / 2), 90, RGBA8(0, 0, 0, 255), 12, "Config Menu");
	
	sftd_draw_text(font_r, 20, 120, RGBA8(120, 118, 115, 255), 12, "Username:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Username:") + 3), 120, RGBA8(67, 72, 66, 255), 12, "%s", username);
	
	sftd_draw_text(font_r, 20, 136, RGBA8(120, 118, 115, 255), 12, "Birthday:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Birthday:") + 3), 136, RGBA8(67, 72, 66, 255), 12, "%s", birthday);
	
	sftd_draw_text(font_r, 20, 152, RGBA8(120, 118, 115, 255), 12, "EULA version:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "EULA version:") + 3), 152, RGBA8(67, 72, 66, 255), 12, "%s", eulaVer);
	
	sftd_draw_text(font_r, 20, 168, RGBA8(120, 118, 115, 255), 12, "Parental control pin:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Parental control pin:") + 3), 168, RGBA8(67, 72, 66, 255), 12, "%s", pin);
	
	/*sftd_draw_text(font_r, 20, 184, RGBA8(120, 118, 115, 255), 12, "Debug mode:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Debug mode:") + 3), 184, RGBA8(67, 72, 66, 255), 12, "%s", isDebugModeEnabled()? "enabled" : "disabled");*/
}

void hardwareMenu(void)
{
	bool hpInserted = false;
	u8 volume = 0;
	
	sftd_draw_text(font_m, ((400 - sftd_get_text_width(font_m, 12, "Hardware Menu")) / 2), 90, RGBA8(0, 0, 0, 255), 12, "Hardware Menu");
	
	DSP_GetHeadphoneStatus(&hpInserted);
	sftd_draw_text(font_r, 20, 120, RGBA8(120, 118, 115, 255), 12, "Headphone status:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Headphone status:") + 3), 120, RGBA8(67, 72, 66, 255), 12, "%s", hpInserted? "inserted" : "not inserted");
	
	sftd_draw_text(font_r, 20, 136, RGBA8(120, 118, 115, 255), 12, "Card slot status:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Card slot status:") + 3), 136, RGBA8(67, 72, 66, 255), 12, "%s", getCardSlotStatus());
	
	sftd_draw_text(font_r, 20, 152, RGBA8(120, 118, 115, 255), 12, "SDMC status:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "SDMC status:") + 3), 152, RGBA8(67, 72, 66, 255), 12, "%s", detectSD()? "detected" : "not detected");
	
	HIDUSER_GetSoundVolume(&volume);
	double volPercent = (volume * 1.5873015873);
	sftd_draw_text(font_r, 20, 168, RGBA8(120, 118, 115, 255), 12, "Volume slider state:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Volume slider state:") + 3), 168, RGBA8(67, 72, 66, 255), 12, "%d (%.0lf%%)", volume, volPercent);
	
	double _3dSliderPercent = (osGet3DSliderState() * 100.0);
	sftd_draw_text(font_r, 20, 184, RGBA8(120, 118, 115, 255), 12, "3D slider state:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "3D slider state:") + 3), 184, RGBA8(67, 72, 66, 255), 12, "%.1lf (%.0lf%%)", osGet3DSliderState(), _3dSliderPercent);

	sftd_draw_text(font_r, 20, 200, RGBA8(120, 118, 115, 255), 12, "Brightness:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Brightness:") + 3), 200, RGBA8(67, 72, 66, 255), 12, "%s", getBrightness(1));
}

void wifiMenu(void)
{
	sf2d_draw_rectangle(0, 19, 400, 221, RGBA8(242, 241, 239, 255));
	
	wifiSlotStructure slotData;
	
	Result wifiRet = CFG_GetConfigInfoBlk8(CFG_WIFI_SLOT_SIZE, CFG_WIFI_BLKID + 0, (u8*)&slotData);
	if ((!wifiRet) && (slotData.set))
	{
		sf2d_draw_rectangle(15, 27, 370, 70, RGBA8(180, 180, 178, 255));
		sf2d_draw_rectangle(16, 28, 368, 68, RGBA8(255, 255, 253, 255));
		
		sftd_draw_text(font_r, 20, 30, RGBA8(120, 118, 115, 255), 12, "WiFi Slot 1:");
		if (slotData.network.use) 
		{
			sftd_draw_textf(font_r, 20, 46, RGBA8(67, 72, 66, 255), 12, "SSID: %s", slotData.network.SSID);
			sftd_draw_textf(font_r, 20, 62, RGBA8(67, 72, 66, 255), 12, "Pass: %s", slotData.network.passphrase);
		}
		else if (slotData.network_WPS.use) 
		{
			sftd_draw_textf(font_r, 20, 46, RGBA8(67, 72, 66, 255), 12, "SSID: %s", slotData.network_WPS.SSID);
			sftd_draw_textf(font_r, 20, 62, RGBA8(67, 72, 66, 255), 12, "Pass: %s", slotData.network_WPS.passphrase);
		}
		sftd_draw_textf(font_r, 20, 78, RGBA8(67, 72, 66, 255), 12, "Mac address: %02X:%02X:%02X:%02X:%02X:%02X", slotData.mac_addr[0], slotData.mac_addr[1], slotData.mac_addr[2], slotData.mac_addr[3], slotData.mac_addr[4], slotData.mac_addr[5]);
	}
	
	wifiRet = CFG_GetConfigInfoBlk8(CFG_WIFI_SLOT_SIZE, CFG_WIFI_BLKID + 1, (u8*)&slotData);
	if ((!wifiRet) && (slotData.set))
	{
		sf2d_draw_rectangle(15, 95, 370, 70, RGBA8(180, 180, 178, 255));
		sf2d_draw_rectangle(16, 96, 368, 68, RGBA8(255, 255, 253, 255));
		
		sftd_draw_text(font_r, 20, 98, RGBA8(120, 118, 115, 255), 12, "WiFi Slot 2:");
		if (slotData.network.use) 
		{
			sftd_draw_textf(font_r, 20, 114, RGBA8(67, 72, 66, 255), 12, "SSID: %s", slotData.network.SSID);
			sftd_draw_textf(font_r, 20, 130, RGBA8(67, 72, 66, 255), 12, "Pass: %s", slotData.network.passphrase);
		}
		else if (slotData.network_WPS.use) 
		{
			sftd_draw_textf(font_r, 20, 114, RGBA8(67, 72, 66, 255), 12, "SSID: %s", slotData.network_WPS.SSID);
			sftd_draw_textf(font_r, 20, 130, RGBA8(67, 72, 66, 255), 12, "Pass: %s", slotData.network_WPS.passphrase);
		}
		sftd_draw_textf(font_r, 20, 146, RGBA8(67, 72, 66, 255), 12, "Mac address: %02X:%02X:%02X:%02X:%02X:%02X", slotData.mac_addr[0], slotData.mac_addr[1], slotData.mac_addr[2], slotData.mac_addr[3], slotData.mac_addr[4], slotData.mac_addr[5]);
	}
	
	wifiRet = CFG_GetConfigInfoBlk8(CFG_WIFI_SLOT_SIZE, CFG_WIFI_BLKID + 2, (u8*)&slotData);
	if ((!wifiRet) && (slotData.set))
	{
		sf2d_draw_rectangle(15, 163, 370, 70, RGBA8(180, 180, 178, 255));
		sf2d_draw_rectangle(16, 164, 368, 68, RGBA8(255, 255, 253, 255));
		
		sftd_draw_text(font_r, 20, 166, RGBA8(120, 118, 115, 255), 12, "WiFi Slot 3:");
		if (slotData.network.use) 
		{
			sftd_draw_textf(font_r, 20, 182, RGBA8(67, 72, 66, 255), 12, "SSID: %s", slotData.network.SSID);
			sftd_draw_textf(font_r, 20, 198, RGBA8(67, 72, 66, 255), 12, "Pass: %s", slotData.network.passphrase);
		}
		else if (slotData.network_WPS.use) 
		{
			sftd_draw_textf(font_r, 20, 182, RGBA8(67, 72, 66, 255), 12, "SSID: %s", slotData.network_WPS.SSID);
			sftd_draw_textf(font_r, 20, 198, RGBA8(67, 72, 66, 255), 12, "Pass: %s", slotData.network_WPS.passphrase);
		}
		sftd_draw_textf(font_r, 20, 214, RGBA8(67, 72, 66, 255), 12, "Mac address: %02X:%02X:%02X:%02X:%02X:%02X", slotData.mac_addr[0], slotData.mac_addr[1], slotData.mac_addr[2], slotData.mac_addr[3], slotData.mac_addr[4], slotData.mac_addr[5]);
	}
}

void storageMenu(void)
{
	u64 sdUsed = 0, sdTotal = 0, ctrUsed = 0, ctrTotal = 0, twlUsed = 0, twlTotal = 0, twlpUsed = 0, twlpTotal = 0; 
	
	char sdFreeSize[16], sdUsedSize[16], sdTotalSize[16];
	char ctrFreeSize[16], ctrUsedSize[16], ctrTotalSize[16];
	char twlFreeSize[16], twlUsedSize[16], twlTotalSize[16];
	char twlpFreeSize[16], twlpUsedSize[16], twlpTotalSize[16];
	
	sf2d_draw_rectangle(0, 19, 400, 221, RGBA8(242, 241, 239, 255));
	
	getSizeString(sdFreeSize, getFreeStorage(SYSTEM_MEDIATYPE_SD));
	getSizeString(sdUsedSize, getUsedStorage(SYSTEM_MEDIATYPE_SD));
	getSizeString(sdTotalSize, getTotalStorage(SYSTEM_MEDIATYPE_SD));
	getSizeString(ctrFreeSize, getFreeStorage(SYSTEM_MEDIATYPE_CTR_NAND));
	getSizeString(ctrUsedSize, getUsedStorage(SYSTEM_MEDIATYPE_CTR_NAND));
	getSizeString(ctrTotalSize, getTotalStorage(SYSTEM_MEDIATYPE_CTR_NAND));
	getSizeString(twlFreeSize, getFreeStorage(SYSTEM_MEDIATYPE_TWL_NAND));
	getSizeString(twlUsedSize, getUsedStorage(SYSTEM_MEDIATYPE_TWL_NAND));
	getSizeString(twlTotalSize, getTotalStorage(SYSTEM_MEDIATYPE_TWL_NAND));
	getSizeString(twlpFreeSize, getFreeStorage(SYSTEM_MEDIATYPE_TWL_PHOTO));
	getSizeString(twlpUsedSize, getUsedStorage(SYSTEM_MEDIATYPE_TWL_PHOTO));
	getSizeString(twlpTotalSize, getTotalStorage(SYSTEM_MEDIATYPE_TWL_PHOTO));
	
	sdUsed = getUsedStorage(SYSTEM_MEDIATYPE_SD);
	sdTotal = getTotalStorage(SYSTEM_MEDIATYPE_SD);
	sf2d_draw_texture(drive, 20, 45);
	sf2d_draw_rectangle(20, 105, 60, 10, RGBA8(120, 118, 115, 255));
	sf2d_draw_rectangle(21, 106, 58, 8, RGBA8(242, 241, 239, 255));
	sf2d_draw_rectangle(21, 106, (((double)sdUsed / (double)sdTotal) * 58.00), 8, RGBA8(242, 119, 62, 255));
	sftd_draw_text(font_r, 85, 50, RGBA8(67, 72, 66, 255), 12, "SD:");
	sftd_draw_text(font_r, 85, 66, RGBA8(120, 118, 115, 255), 12, "Free:");
	sftd_draw_text(font_r, 85, 82, RGBA8(120, 118, 115, 255), 12, "Used:");
	sftd_draw_text(font_r, 85, 98, RGBA8(120, 118, 115, 255), 12, "Total:");
	sftd_draw_textf(font_r, (85 + sftd_get_text_width(font_r, 12, "Free:") + 3), 66, RGBA8(67, 72, 66, 255), 12, "%s", sdFreeSize);
	sftd_draw_textf(font_r, (85 + sftd_get_text_width(font_r, 12, "Used:") + 3), 82, RGBA8(67, 72, 66, 255), 12, "%s", sdUsedSize);
	sftd_draw_textf(font_r, (85 + sftd_get_text_width(font_r, 12, "Total:") + 3), 98, RGBA8(67, 72, 66, 255), 12, "%s", sdTotalSize);
	
	ctrUsed = getUsedStorage(SYSTEM_MEDIATYPE_CTR_NAND);
	ctrTotal = getTotalStorage(SYSTEM_MEDIATYPE_CTR_NAND);
	sf2d_draw_texture(drive, 220, 45);
	sf2d_draw_rectangle(220, 105, 60, 10, RGBA8(120, 118, 115, 255));
	sf2d_draw_rectangle(221, 106, 58, 8, RGBA8(242, 241, 239, 255));
	sf2d_draw_rectangle(221, 106, (((double)ctrUsed / (double)ctrTotal) * 58.00), 8, RGBA8(242, 119, 62, 255));
	sftd_draw_text(font_r, 285, 50, RGBA8(67, 72, 66, 255), 12, "CTR Nand:");
	sftd_draw_text(font_r, 285, 66, RGBA8(120, 118, 115, 255), 12, "Free:");
	sftd_draw_text(font_r, 285, 82, RGBA8(120, 118, 115, 255), 12, "Used:");
	sftd_draw_text(font_r, 285, 98, RGBA8(120, 118, 115, 255), 12, "Total:");
	sftd_draw_textf(font_r, (285 + sftd_get_text_width(font_r, 12, "Free:") + 3), 66, RGBA8(67, 72, 66, 255), 12, "%s", ctrFreeSize);
	sftd_draw_textf(font_r, (285 + sftd_get_text_width(font_r, 12, "Used:") + 3), 82, RGBA8(67, 72, 66, 255), 12, "%s", ctrUsedSize);
	sftd_draw_textf(font_r, (285 + sftd_get_text_width(font_r, 12, "Total:") + 3), 98, RGBA8(67, 72, 66, 255), 12, "%s", ctrTotalSize);
	
	twlUsed = getUsedStorage(SYSTEM_MEDIATYPE_TWL_NAND);
	twlTotal = getTotalStorage(SYSTEM_MEDIATYPE_TWL_NAND);
	sf2d_draw_texture(drive, 20, 140);
	sf2d_draw_rectangle(20, 200, 60, 10, RGBA8(120, 118, 115, 255));
	sf2d_draw_rectangle(21, 201, 58, 8, RGBA8(242, 241, 239, 255));
	sf2d_draw_rectangle(21, 201, (((double)twlUsed / (double)twlTotal) * 58.00), 8, RGBA8(242, 119, 62, 255));
	sftd_draw_text(font_r, 85, 145, RGBA8(67, 72, 66, 255), 12, "TWL Nand:");
	sftd_draw_text(font_r, 85, 161, RGBA8(120, 118, 115, 255), 12, "Free:");
	sftd_draw_text(font_r, 85, 177, RGBA8(120, 118, 115, 255), 12, "Used:");
	sftd_draw_text(font_r, 85, 193, RGBA8(120, 118, 115, 255), 12, "Total:");
	sftd_draw_textf(font_r, (85 + sftd_get_text_width(font_r, 12, "Free:") + 3), 161, RGBA8(67, 72, 66, 255), 12, "%s", twlFreeSize);
	sftd_draw_textf(font_r, (85 + sftd_get_text_width(font_r, 12, "Used:") + 3), 177, RGBA8(67, 72, 66, 255), 12, "%s", twlUsedSize);
	sftd_draw_textf(font_r, (85 + sftd_get_text_width(font_r, 12, "Total:") + 3), 193, RGBA8(67, 72, 66, 255), 12, "%s", twlTotalSize);
	
	twlpUsed = getUsedStorage(SYSTEM_MEDIATYPE_TWL_PHOTO);
	twlpTotal = getTotalStorage(SYSTEM_MEDIATYPE_TWL_PHOTO);
	sf2d_draw_texture(drive, 220, 140);
	sf2d_draw_rectangle(220, 200, 60, 10, RGBA8(120, 118, 115, 255));
	sf2d_draw_rectangle(221, 201, 58, 8, RGBA8(242, 241, 239, 255));
	sf2d_draw_rectangle(221, 201, (((double)twlpUsed / (double)twlpTotal) * 58.00), 8, RGBA8(242, 119, 62, 255));
	sftd_draw_text(font_r, 285, 145, RGBA8(67, 72, 66, 255), 12, "TWL Photo:");
	sftd_draw_text(font_r, 285, 161, RGBA8(120, 118, 115, 255), 12, "Free:");
	sftd_draw_text(font_r, 285, 177, RGBA8(120, 118, 115, 255), 12, "Used:");
	sftd_draw_text(font_r, 285, 193, RGBA8(120, 118, 115, 255), 12, "Total:");
	sftd_draw_textf(font_r, (285 + sftd_get_text_width(font_r, 12, "Free:") + 3), 161, RGBA8(67, 72, 66, 255), 12, "%s", twlpFreeSize);
	sftd_draw_textf(font_r, (285 + sftd_get_text_width(font_r, 12, "Used:") + 3), 177, RGBA8(67, 72, 66, 255), 12, "%s", twlpUsedSize);
	sftd_draw_textf(font_r, (285 + sftd_get_text_width(font_r, 12, "Total:") + 3), 193, RGBA8(67, 72, 66, 255), 12, "%s", twlpTotalSize);
}

void miscMenu(void)
{	
	double wifiPercent = (osGetWifiStrength() * 33.3333333333);
	
	sftd_draw_text(font_m, ((400 - sftd_get_text_width(font_m, 12, "Miscellaneous")) / 2), 90, RGBA8(0, 0, 0, 255), 12, "Miscellaneous");
	
	sftd_draw_text(font_r, 20, 120, RGBA8(120, 118, 115, 255), 12, "Installed titles:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Installed titles:") + 3), 120, RGBA8(67, 72, 66, 255), 12, "SD: %lu (NAND: %lu)", titleCount(MEDIATYPE_SD), titleCount(MEDIATYPE_NAND));
	
	u64 homemenuID = 0;
	Result ret = APT_GetAppletInfo(APPID_HOMEMENU, &homemenuID, NULL, NULL, NULL, NULL);
	sftd_draw_text(font_r, 20, 136, RGBA8(120, 118, 115, 255), 12, "Homemenu ID:");
	if(ret == 0)
		sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "Homemenu ID:") + 3), 136, RGBA8(67, 72, 66, 255), 12, "%016llX", homemenuID);
	
	sftd_draw_text(font_r, 20, 152, RGBA8(120, 118, 115, 255), 12, "WiFi signal strength:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "WiFi signal strength:") + 3), 152, RGBA8(67, 72, 66, 255), 12, "%d (%.0lf%%)", osGetWifiStrength(), wifiPercent);
	
	u32 ip = gethostid();
	sftd_draw_text(font_r, 20, 168, RGBA8(120, 118, 115, 255), 12, "IP:");
	sftd_draw_textf(font_r, (20 + sftd_get_text_width(font_r, 12, "IP:") + 3), 168, RGBA8(67, 72, 66, 255), 12, "%lu.%lu.%lu.%lu", ip & 0xFF, (ip>>8)&0xFF, (ip>>16)&0xFF, (ip>>24)&0xFF);
}

void initServices(void)
{
	dspInit();
	cfguInit();
	cfgsInit();
	fsInit();
	sdmcInit();
	openArchive(ARCHIVE_SDMC);
	ptmuInit();
	mcuInit();
	amInit(); 
	amAppInit();
	psInit();
	aptInit();
	hidInit();
	actInit(SDK(11, 2, 0, 200), 0x20000);
	socInit((u32*)memalign(0x1000, 0x10000), 0x10000);
	
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0, 0, 0, 255));
	sf2d_set_vblank_wait(1);
	
	sftd_init();
	romfsInit();
	
	topScreen = sfil_load_PNG_file("romfs:/res/topScreen.png", SF2D_PLACE_RAM); setBilinearFilter(topScreen);
	bottomScreen = sfil_load_PNG_file("romfs:/res/bottomScreen.png", SF2D_PLACE_RAM); setBilinearFilter(bottomScreen);
	logo = sfil_load_PNG_file("romfs:/res/icon.png", SF2D_PLACE_RAM); setBilinearFilter(logo);
	drive = sfil_load_PNG_file("romfs:/res/drive.png", SF2D_PLACE_RAM); setBilinearFilter(drive);
	
	font_m = sftd_load_font_mem(UbuntuMedium_ttf, UbuntuMedium_ttf_size);
	font_r = sftd_load_font_mem(UbuntuRegular_ttf, UbuntuRegular_ttf_size);
	
	if (isN3DS())
		osSetSpeedupEnable(true);
	
	// Simply because I don't want the following constantly being checked for in a while loop.
	
	strcpy(kernerlVersion, getVersion(0));
	strcpy(firmVersion, getVersion(1));
	strcpy(systemVersion, getVersion(2));
	strncpy(sdmcCID, getCID(0), 33);
	strncpy(nandCID, getCID(1), 33);
	strncpy(username, getUsername(), 15);
	strncpy(birthday, getBirthday(), 6);
	strncpy(eulaVer, getEulaVersion(), 6);
	strncpy(pin, getParentalPin(), 6);
}

void termServices(void)
{
	osSetSpeedupEnable(0);
	
	sftd_free_font(font_r);
	sftd_free_font(font_m);
	
	sf2d_free_texture(logo);
	sf2d_free_texture(bottomScreen);
	sf2d_free_texture(topScreen);
	
	sftd_fini();
	romfsExit();
	sf2d_fini();
    socExit();
	actExit();
	hidExit();
	aptExit();
	psExit();
	acExit();
	amExit();
	httpcExit();
	mcuExit();
	ptmuExit();
	closeArchive();
	sdmcExit();
	fsExit();
	cfgsExit();
	cfguExit();
	dspExit();
}

int	touchButton(touchPosition *touch, int MenuSelection)
{
	if (touch->px >= 15 && touch->px <= 300 && touch->py >= 37 && touch->py <= 56)
		MenuSelection = 1;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 56 && touch->py <= 73)
		MenuSelection = 2;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 73 && touch->py <= 92)
		MenuSelection = 3;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 92 && touch->py <= 110)
		MenuSelection = 4;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 110 && touch->py <= 127)
		MenuSelection = 5;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 127 && touch->py <= 144)
		MenuSelection = 6;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 144 && touch->py <= 161)
		MenuSelection = 7;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 161 && touch->py <= 178)
		MenuSelection = 8;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 178 && touch->py <= 195)	
		MenuSelection = 9;
	else if (touch->px >= 15 && touch->px <= 300 && touch->py >= 195 && touch->py <= 212)	
		MenuSelection = 10;
	
	return MenuSelection;
}

int main(int argc, char *argv[])
{      
	initServices();
	
	int MenuSelection = 1; // Pretty obvious
	int selector_x = 16; //The x position of the first selection
	int selector_y = 17; //The y position of the first selection
	int numMenuItems = 10; //Amount of items in the menu
	int selector_image_x = 0; //Determines the starting x position of the selection
	int selector_image_y = 0; //Determines the starting y position of the selection
	touchPosition touch;
	
	while (aptMainLoop())
    {
		selector_image_x = selector_x + (selector_xDistance * MenuSelection); //Determines where the selection image is drawn for each selection
		selector_image_y = selector_y + (selector_yDistance * MenuSelection); //Determines where the selection image is drawn for each selection
		
		hidScanInput();
		hidTouchRead(&touch);
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		
		MenuSelection = touchButton(&touch, MenuSelection);
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		
		sf2d_draw_texture(bottomScreen, 0, 0);
		sf2d_draw_rectangle(selector_image_x, selector_image_y, 286, 18, RGBA8(242, 119, 62, 255));
		
		if (MenuSelection == 1)
			sftd_draw_text(font_m, 22, 37, RGBA8(250, 237, 227, 255), 12, "Kernel Information");
		else 
			sftd_draw_text(font_m, 22, 37, RGBA8(78, 74, 67, 255), 12, "Kernel Information");
		
		if (MenuSelection == 2)
			sftd_draw_text(font_m, 22, 55, RGBA8(250, 237, 227, 255), 12, "System Information");
		else
			sftd_draw_text(font_m, 22, 55, RGBA8(78, 74, 67, 255), 12, "System Information");
		
		if (MenuSelection == 3)
			sftd_draw_text(font_m, 22, 73, RGBA8(250, 237, 227, 255), 12, "Battery Information");
		else
			sftd_draw_text(font_m, 22, 73, RGBA8(78, 74, 67, 255), 12, "Battery Information");
		
		if (MenuSelection == 4)
			sftd_draw_text(font_m, 22, 91, RGBA8(250, 237, 227, 255), 12, "NNID Information");
		else
			sftd_draw_text(font_m, 22, 91, RGBA8(78, 74, 67, 255), 12, "NNID Information");
		
		if (MenuSelection == 5)
			sftd_draw_text(font_m, 22, 109, RGBA8(250, 237, 227, 255), 12, "Config Information");
		else
			sftd_draw_text(font_m, 22, 109, RGBA8(78, 74, 67, 255), 12, "Config Information");
		
		if (MenuSelection == 6)
			sftd_draw_text(font_m, 22, 127, RGBA8(250, 237, 227, 255), 12, "Hardware Information");
		else
			sftd_draw_text(font_m, 22, 127, RGBA8(78, 74, 67, 255), 12, "Hardware Information");
		
		if (MenuSelection == 7)
			sftd_draw_text(font_m, 22, 145, RGBA8(250, 237, 227, 255), 12, "WiFi Information");
		else
			sftd_draw_text(font_m, 22, 145, RGBA8(78, 74, 67, 255), 12, "WiFi Information");
		
		if (MenuSelection == 8)
			sftd_draw_text(font_m, 22, 163, RGBA8(250, 237, 227, 255), 12, "Storage Information");
		else
			sftd_draw_text(font_m, 22, 163, RGBA8(78, 74, 67, 255), 12, "Storage Information");
		
		if (MenuSelection == 9)
			sftd_draw_text(font_m, 22, 181, RGBA8(250, 237, 227, 255), 12, "Miscellaneous");
		else
			sftd_draw_text(font_m, 22, 181, RGBA8(78, 74, 67, 255), 12, "Miscellaneous");
		
		if (MenuSelection == 10)
			sftd_draw_text(font_m, 22, 199, RGBA8(250, 237, 227, 255), 12, "Exit");
		else
			sftd_draw_text(font_m, 22, 199, RGBA8(78, 74, 67, 255), 12, "Exit");
		
		//Added delay to prevent text from appearing 'glitchy' as you scroll past each section.
		if (kDown & KEY_DDOWN)
			MenuSelection++; //Moves the selector down
		else if (kDown & KEY_DUP)
			MenuSelection--; //Moves the selector up
		
		if (kHeld & KEY_CPAD_DOWN)
		{
			svcSleepThread(50000000);
			MenuSelection++; //Moves the selector down
		}
		else if (kHeld & KEY_CPAD_UP)
		{
			svcSleepThread(50000000);
			MenuSelection--; //Moves the selector up
		}
        
		if (MenuSelection > numMenuItems) 
			MenuSelection = 1; //Sets the selection to the first
		if (MenuSelection < 1) 
			MenuSelection = numMenuItems; //Sets the selection back to last
		
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
        		
		sf2d_draw_texture(topScreen, 0, 0);
		sf2d_draw_texture(logo, 180, 36);
		
		sftd_draw_text(font_m, 5, 1, RGBA8(250, 237, 227, 255), 12, "3DSident v0.7.6");
		
		if (MenuSelection == 1)
			kernelMenu();
		else if (MenuSelection == 2)
			systemMenu();
		else if (MenuSelection == 3)
			batteryMenu();
		else if (MenuSelection == 4)
			NNIDInfoMenu();
		else if (MenuSelection == 5)
			configInfoMenu();
		else if (MenuSelection == 6)
			hardwareMenu();
		else if (MenuSelection == 7)
			wifiMenu();
		else if (MenuSelection == 8)
			storageMenu();
		else if (MenuSelection == 9)
			miscMenu();
		
		endDrawing();
		
		if (((MenuSelection == 10) && ((kDown & KEY_A) || (kDown & KEY_TOUCH))) || (kDown & KEY_START))
			break;
		
		if ((kHeld & KEY_L) && (kHeld & KEY_R))
			captureScreenshot();
	}
	
	termServices();
	
	return 0;	
}