#pragma once

template <typename... TConfigs>
using ConfigVariant = std::variant<std::shared_ptr<const TConfigs>...>;