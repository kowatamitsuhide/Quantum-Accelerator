#include "C_DIS.h"

std::list<C_Distance*> C_Distance::c_dis_list = {};

void C_Distance::Init()
{
	c_dis_list.push_back(this);
	tag = "default";
}

void C_Distance::IsRemove()
{
	auto is_it = c_dis_list.begin();
	while (is_it != c_dis_list.end()) {
		if ((*is_it) != this) {
			is_it++;}
		else {
			is_it = c_dis_list.erase(is_it);
			return;
		}
	}
}

void C_Distance::IsTagSet(std::string _tag)
{ 
	ASSERT(_tag != "default" && "defaultˆÈŠO‚É‚µ‚Ä‚­‚¾‚³‚¢B");
	tag = _tag;
};

bool C_Distance::TagSerch(std::string _tag)
{
	bool flag = false;
	for (auto&& h : c_dis_list) {
		if (h->tag == _tag) { flag = true; };
	}
	return flag;
}

std::vector<C_Distance*> C_Distance::DistanceList(std::string _tag)
{
	std::vector<C_Distance*>  c_dis;
	for (auto&& h : c_dis_list) {
		if (h->tag != _tag)          continue;
		if (h->GetThisDis() == this) continue;
		c_dis.push_back(h->GetThisDis());
	}
	return c_dis;
};


std::vector<float> C_Distance::IsOtherTagDistance(std::vector<C_Distance*> tag_c_dis)
{
	std::vector<float> at_distance;
	for (auto&& other : tag_c_dis) 
	{
		float other_distance = Vector3_Distance(other->gameObject->transform.position, this->gameObject->transform.position);
		at_distance.push_back(other_distance);
	}
	return at_distance;
};

float C_Distance::GetTagDistance(std::string _tag)
{
	ASSERT(TagSerch(_tag) && "tag‚ª‘¶İ‚µ‚Ä‚¢‚È‚¢!");

	std::vector<C_Distance*> c_dis = DistanceList(_tag);

	if (c_dis.size() != 0){
		std::vector<float> at_distance = IsOtherTagDistance(c_dis);

		auto&& tag_min_distance = *std::min_element(at_distance.begin(), at_distance.end(), [](float a, float b) {return a < b; });
		return tag_min_distance;
	}
	return FLT_MAX;
}

