#include "emsdata.h"

EmsData::EmsData()
{
}
QByteArray EmsData::getLocalRamBlock(unsigned short id)
{
	for (int i=0;i<m_ramMemoryList.size();i++)
	{
		if (m_ramMemoryList[i]->locationid == id)
		{
			return m_ramMemoryList[i]->data();
		}
	}
	return QByteArray();
}

QByteArray EmsData::getLocalFlashBlock(unsigned short id)
{
	for (int i=0;i<m_flashMemoryList.size();i++)
	{
		if (m_flashMemoryList[i]->locationid == id)
		{
			return m_flashMemoryList[i]->data();
		}
	}
	return QByteArray();
}
QByteArray EmsData::getDeviceRamBlock(unsigned short id)
{
	for (int i=0;i<m_deviceRamMemoryList.size();i++)
	{
		if (m_deviceRamMemoryList[i]->locationid == id)
		{
			return m_deviceRamMemoryList[i]->data();
		}
	}
	return QByteArray();
}

QByteArray EmsData::getDeviceFlashBlock(unsigned short id)
{
	for (int i=0;i<m_deviceFlashMemoryList.size();i++)
	{
		if (m_deviceFlashMemoryList[i]->locationid == id)
		{
			return m_deviceFlashMemoryList[i]->data();
		}
	}
	return QByteArray();
}

bool EmsData::hasDeviceRamBlock(unsigned short id)
{
	for (int i=0;i<m_deviceRamMemoryList.size();i++)
	{
		if (m_deviceRamMemoryList[i]->locationid == id)
		{
			return true;
		}
	}
	return false;
}
bool EmsData::hasLocalRamBlock(unsigned short id)
{
	for (int i=0;i<m_ramMemoryList.size();i++)
	{
		if (m_ramMemoryList[i]->locationid == id)
		{
			return true;
		}
	}
	return false;
}
void EmsData::setLocalRamBlock(unsigned short id,QByteArray data)
{
	for (int i=0;i<m_ramMemoryList.size();i++)
	{
		if (m_ramMemoryList[i]->locationid == id)
		{
			m_ramMemoryList[i]->setData(data);
			return;
		}
	}
}

void EmsData::setDeviceRamBlock(unsigned short id,QByteArray data)
{
	for (int i=0;i<m_deviceRamMemoryList.size();i++)
	{
		if (m_deviceRamMemoryList[i]->locationid == id)
		{
			m_deviceRamMemoryList[i]->setData(data);
			return;
		}
	}
}

void EmsData::setLocalFlashBlock(unsigned short id,QByteArray data)
{
	for (int i=0;i<m_flashMemoryList.size();i++)
	{
		if (m_flashMemoryList[i]->locationid == id)
		{
			m_flashMemoryList[i]->setData(data);
			return;
		}
	}
}

bool EmsData::hasLocalFlashBlock(unsigned short id)
{
	for (int i=0;i<m_flashMemoryList.size();i++)
	{
		if (m_flashMemoryList[i]->locationid == id)
		{
			return true;
		}
	}
	return false;
}
bool EmsData::hasDeviceFlashBlock(unsigned short id)
{
	for (int i=0;i<m_deviceFlashMemoryList.size();i++)
	{
		if (m_deviceFlashMemoryList[i]->locationid == id)
		{
			return true;
		}
	}
	return false;
}
void EmsData::populateDeviceRamAndFlashParents()
{
	for (int i=0;i<m_deviceFlashMemoryList.size();i++)
	{
		if (m_deviceFlashMemoryList[i]->hasParent && m_deviceFlashMemoryList[i]->getParent() == 0)
		{
			for (int j=0;j<m_deviceFlashMemoryList.size();j++)
			{
				if (m_deviceFlashMemoryList[i]->parent== m_deviceFlashMemoryList[j]->locationid)
				{
					m_deviceFlashMemoryList[i]->setParent(m_deviceFlashMemoryList[j]);
				}
			}
		}
	}
	for (int i=0;i<m_deviceRamMemoryList.size();i++)
	{
		if (m_deviceRamMemoryList[i]->hasParent && m_deviceRamMemoryList[i]->getParent() == 0)
		{
			for (int j=0;j<m_deviceRamMemoryList.size();j++)
			{
				if (m_deviceRamMemoryList[i]->parent== m_deviceRamMemoryList[j]->locationid)
				{
					m_deviceRamMemoryList[i]->setParent(m_deviceRamMemoryList[j]);
				}
			}
		}
	}
}

void EmsData::setDeviceFlashBlock(unsigned short id,QByteArray data)
{
	for (int i=0;i<m_deviceFlashMemoryList.size();i++)
	{
		if (m_deviceFlashMemoryList[i]->locationid == id)
		{
			m_deviceFlashMemoryList[i]->setData(data);
			return;
		}
	}
}

void EmsData::clearAllMemory()
{
	m_deviceFlashMemoryList.clear();
	m_deviceRamMemoryList.clear();
	m_flashMemoryList.clear();
	m_ramMemoryList.clear();
}
void EmsData::addDeviceRamBlock(MemoryLocation *loc)
{
	m_deviceRamMemoryList.append(loc);
}

void EmsData::addLocalFlashBlock(MemoryLocation *loc)
{
	m_flashMemoryList.append(loc);
}

void EmsData::addLocalRamBlock(MemoryLocation *loc)
{
	m_ramMemoryList.append(loc);
}

void EmsData::addDeviceFlashBlock(MemoryLocation *loc)
{
	m_deviceFlashMemoryList.append(loc);
}
QList<unsigned short> EmsData::getChildrenOfLocalRamLocation(unsigned short id)
{
	QList<unsigned short> retVal;
	for (int i=0;i<m_ramMemoryList.size();i++)
	{
		if (m_ramMemoryList[i]->parent == id)
		{
			retVal.append(m_ramMemoryList[i]->locationid);
		}
	}
	return retVal;
}

QList<unsigned short> EmsData::getParentOfLocalRamLocation(unsigned short id)
{
	QList<unsigned short> retVal;

	for (int i=0;i<m_ramMemoryList.size();i++)
	{
		if (m_ramMemoryList[i]->locationid == id)
		{
			retVal.append(m_ramMemoryList[i]->parent);
		}
	}
	return retVal;
}
bool EmsData::localRamHasParent(unsigned short id)
{
	for (int i=0;i<m_ramMemoryList.size();i++)
	{
		if (m_ramMemoryList[i]->locationid == id)
		{
			return m_ramMemoryList[i]->hasParent;
		}
	}
	return false;
}
QList<unsigned short> EmsData::getTopLevelDeviceFlashLocations()
{
	QList<unsigned short> retval;
	for (int i=0;i<m_deviceFlashMemoryList.size();i++)
	{
		if (!m_deviceFlashMemoryList[i]->hasParent)
		{
			retval.append(m_deviceFlashMemoryList[i]->locationid);
		}
	}
	return retval;
}
void EmsData::populateLocalRamAndFlash()
{
	if (m_ramMemoryList.size() == 0)
	{
		//Internal ram list is empty. Let's fill it.
		for (int i=0;i<m_deviceRamMemoryList.size();i++)
		{
			m_ramMemoryList.append(new MemoryLocation(*m_deviceRamMemoryList[i]));
		}
		//We have to do something special here, since m_ramMemoryList's parents point to m_deviceRamMemoryList.
		for (int i=0;i<m_ramMemoryList.size();i++)
		{
			if (m_ramMemoryList[i]->hasParent)
			{
				for (int j=0;j<m_ramMemoryList.size();j++)
				{
					if (m_ramMemoryList[i]->parent== m_ramMemoryList[j]->locationid)
					{
						m_ramMemoryList[i]->setParent(m_ramMemoryList[j]);
					}
				}
			}
		}
	}
	if (m_flashMemoryList.size() == 0)
	{
		for (int i=0;i<m_deviceFlashMemoryList.size();i++)
		{
			m_flashMemoryList.append(new MemoryLocation(*m_deviceFlashMemoryList[i]));
		}
		//We have to do something special here, since m_ramMemoryList's parents point to m_deviceRamMemoryList.
		for (int i=0;i<m_flashMemoryList.size();i++)
		{
			if (m_flashMemoryList[i]->hasParent)
			{
				for (int j=0;j<m_flashMemoryList.size();j++)
				{
					if (m_flashMemoryList[i]->parent== m_flashMemoryList[j]->locationid)
					{
						m_flashMemoryList[i]->setParent(m_flashMemoryList[j]);
					}
				}
			}
		}
	}
}

QList<unsigned short> EmsData::getTopLevelDeviceRamLocations()
{
	QList<unsigned short> retval;
	for (int i=0;i<m_deviceRamMemoryList.size();i++)
	{
		if (!m_deviceRamMemoryList[i]->hasParent)
		{
			retval.append(m_deviceRamMemoryList[i]->locationid);
		}
	}
	return retval;
}

bool EmsData::localRamHasChildren(unsigned short id)
{
	for (int i=0;i<m_flashMemoryList.size();i++)
	{
		if (m_flashMemoryList[i]->locationid == id)
		{
			return m_flashMemoryList[i]->hasParent;
		}
	}
	return false;
}
QString EmsData::serialize(bool withdata)
{
	Q_UNUSED(withdata)
	return "";
}
