#include "pch.h"
#include "Hittable.h"

void HittableList::add(std::shared_ptr<Hittable> hittable)
{
	m_List.push_back(hittable);
}

HitRecord HittableList::hit(const Ray& ray, float tMin, float tMax) const
{
	HitRecord rec;
	for (const auto& obj : m_List)
	{
		HitRecord temp = obj->hit(ray, tMin, tMax);
		if (temp.collides && (temp.t < rec.t || rec.t == 0.0f))
		{
			rec = temp;
		}
	}
	return rec;
}
