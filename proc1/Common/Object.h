#pragma once

class Object
{
public:
	Object() {}
	virtual ~Object() {}

	void SetGUID(uint64_t guid) { mGUID = guid; mGUIDStr = std::to_string(guid); }
	uint64_t GetGUID() const { return mGUID; }

    const std::string & GetGUIDAsString() const { return mGUIDStr; }

    void SetName(std::string name) { mName = std::move(name); }
    const std::string & GetName() const { return mName; }

	void SetAlias(std::string alias) { mAlias = std::move(alias); }
	const std::string& GetAlias() const { return mAlias; }
public:
	virtual void Update(int32_t delta) {};

protected:
	uint64_t        mGUID = 0;
    std::string     mGUIDStr = "";
	// LuaHost中有改变Name的接口,RoleItem中该Name不能当做KeyName
    std::string     mName = "";
	std::string		mAlias = "";
};
