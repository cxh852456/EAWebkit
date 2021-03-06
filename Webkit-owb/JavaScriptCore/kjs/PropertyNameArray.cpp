// -*- mode: c++; c-basic-offset: 4 -*-
/*
 *  Copyright (C) 2006, 2008 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"
#include "PropertyNameArray.h"

namespace KJS {

static const size_t setThreshold = 20;

void PropertyNameArray::add(UString::Rep* identifier)
{
    ASSERT(identifier == &UString::Rep::null || identifier == &UString::Rep::empty || identifier->identifierTable);

    size_t size = m_vector.size();
    if (size < setThreshold) {
        for (size_t i = 0; i < size; ++i) {
            if (identifier == m_vector[i].ustring().rep())
                return;
        }
    } else {
        if (m_set.isEmpty()) {
            for (size_t i = 0; i < size; ++i)
                m_set.add(m_vector[i].ustring().rep());
        }
        if (!m_set.add(identifier).second)
            return;
    }

    m_vector.append(Identifier(m_globalData, identifier));
}

} // namespace KJS
