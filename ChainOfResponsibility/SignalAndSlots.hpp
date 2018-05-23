#ifndef SIGNALANDSLOTS_HPP
#define SIGNALANDSLOTS_HPP

#include <functional>
#include <map>
#include <memory>

template < typename... Args > class Signal
{
 public:
   class Slot
   {
      const Signal* signal{nullptr};
      std::function< void(Args...) > callback;
      const size_t id;

    public:
      explicit Slot(const Signal* s, std::function< void(Args...) > cb, const size_t id) : signal(s), callback(cb), id(id)
      {
      }

      Slot(Slot&&) noexcept = default;
      Slot&
      operator=(Slot&&) noexcept = default;

      ~Slot()
      {
         disconnect();
      }

      void
      disconnect()
      {
         if (signal)
         {
            signal->disconnect(id);
         }
      }

      void
      setCallback(std::function< void(Args...) > cb)
      {
         callback = cb;
      }

      friend class Signal;
   };

   using Connection = std::shared_ptr< Slot >;

   Signal() = default;
   Signal(Signal const&) = delete;
   Signal(Signal&&) noexcept = default;
   Signal&
   operator=(Signal const&) = delete;
   Signal&
   operator=(Signal&&) noexcept = delete;

   ~Signal()
   {
      disconnect_all();
   }


   std::shared_ptr< Slot >
   connect(std::function< void(Args...) > callback) const
   {
      auto const id = getAvailableId();
      auto slot = std::make_shared< Slot >(this, std::move(callback), id);
      mSlots.insert(std::make_pair(id, slot));
      return slot;
   }

   size_t
   getAvailableId() const
   {
      do
      {
         ++mCurrentSlotId;
      } while (mSlots.count(mCurrentSlotId) == 1);

      return mCurrentSlotId;
   }


   void
   disconnect(const size_t id) const
   {
      if (mSlots.count(id))
      {
         auto slot = mSlots[id].lock();
         if (slot)
         {
            slot->signal = nullptr;
         }
         mSlots.erase(id);
      }
   }

   void
   disconnect_all() const
   {
      for (auto& slotEntry : mSlots)
      {
         auto slot = slotEntry.second.lock();
         if (slot)
         {
            slot->signal = nullptr;
         }
      }
      mSlots.clear();
   }

   // calls all connected functions
   void
   operator()(Args... p)
   {
      for (auto slotEntry : mSlots)
      {
         auto slot = slotEntry.second.lock();
         if (slot)
            slot->callback(p...);
      }
   }

 private:
   mutable std::map< size_t, std::weak_ptr< Slot > > mSlots;
   mutable size_t mCurrentSlotId{0};
};


#endif // SIGNALANDSLOTS_HPP
