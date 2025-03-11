#ifndef __UID__HPP__
#define __UID__HPP__

#include <cstdint>
#include "ibuffermanager.hpp"
#include "uid_c.hpp"

class Uid : public IBuffermanager
{
public:
	explicit Uid();
	Uid(const Uid& other_) = default;
	uint8_t* ToBuffer(uint8_t*) override;
    uint8_t* FromBuffer(uint8_t*) override;
    uint64_t GetBufferSize() const override;
	const my_uid_t& GetUidData() const; 
	bool operator==(const Uid& other) const; 
	void Print_Object() const override;
	~Uid() override = default;
private:
	my_uid_t m_uid;
};

#endif // __UID__HPP__
