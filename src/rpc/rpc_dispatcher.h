/*
 * CONCLAVE - Scaling Bitcoin Simply.
 * Copyright (C) 2019-2021 Conclave development team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "../worker.h"
#include "../mongoose/mongoose.h"
#include "../util/concurrent_list.h"
#include "methods/response.h"

namespace conclave
{
    namespace rpc
    {
        class RpcDispatcher final : public Worker
        {
            public:
            RpcDispatcher(const unsigned int, ConcurrentList<Response*>&);
            private:
            void work() override final;
            const unsigned int id;
            ConcurrentList<Response*>& responseQueue;
        };
    }
}
