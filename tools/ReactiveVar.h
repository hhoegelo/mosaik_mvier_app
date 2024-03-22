#pragma once

#include <glibmm/refptr.h>
#include <glibmm/main.h>

#include <utility>
#include <memory>
#include <set>
#include <algorithm>
#include <functional>

namespace Tools
{
  class Computations
  {
   public:
    class Computation;

    virtual ~Computations();
    void add(const std::function<void()>& cb);

   protected:
    virtual void onComputationInvalidated(Computation* c) = 0;
    std::vector<std::shared_ptr<Computation>> m_computations;
  };

  class ImmediateComputations : public Computations
  {
   private:
    void onComputationInvalidated(Computation* c) override;
  };

  class DeferredComputations : public Computations
  {
   public:
    DeferredComputations(Glib::RefPtr<Glib::MainContext> ctx);
    ~DeferredComputations() override;

   private:
    void onComputationInvalidated(Computation* c) override;

    Glib::RefPtr<Glib::MainContext> m_ctx;
    sigc::connection m_timer;
  };

  class ReactiveVarBase
  {
   public:
    ReactiveVarBase();
    virtual ~ReactiveVarBase();

   protected:
    void registerCurrentComputation() const;
    void invalidate();

    mutable std::set<std::weak_ptr<Computations::Computation>, std::owner_less<>> m_listeners;
  };

  template <typename T> class ReactiveVar : public ReactiveVarBase
  {
   public:
    explicit ReactiveVar(const T& init)
        : m_value(init)
    {
    }

    ~ReactiveVar() override = default;

    ReactiveVar<T>& operator=(const T& v)
    {
      if(std::exchange(m_value, v) != v)
        invalidate();
      return *this;
    }

    explicit operator const T&() const
    {
      registerCurrentComputation();
      return m_value;
    }

    operator T() const  // NOLINT
    {
      registerCurrentComputation();
      return m_value;
    }

    const T& get() const
    {
      registerCurrentComputation();
      return m_value;
    }

   private:
    T m_value;
  };

}