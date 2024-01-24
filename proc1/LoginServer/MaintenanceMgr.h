#pragma once
class MaintenanceMgr
{
	DECL_SINGLETON(MaintenanceMgr);
public:
	MaintenanceMgr() :mMaintenanceIng(false) {};
	~MaintenanceMgr() {};

	void SetMaintence() { mMaintenanceIng = true; };
	void ReSetMaintence() { mMaintenanceIng = false; };
	bool IsMaintenceIng() { return mMaintenanceIng; };

private:
	bool mMaintenanceIng;
};