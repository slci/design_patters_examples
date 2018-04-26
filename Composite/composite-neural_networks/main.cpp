#include <iostream>
#include <vector>

// CRTP Neuron
template < typename Self > struct Connectable
{
   template < typename T >
   void
   connect_to(T& other)
   {
      for (auto& from : static_cast< Self& >(*this))
      {
         for (auto& to : other)
         {
            from.outputs.push_back(&to);
            to.inputs.push_back(&from);
         }
      }
   }
};

struct Neuron : Connectable< Neuron >
{
   unsigned id;
   std::vector< Neuron* > inputs;
   std::vector< Neuron* > outputs;

   Neuron()
   {
      static unsigned id{0};
      this->id = id++;
   }

   friend std::ostream&
   operator<<(std::ostream& os, const Neuron& neuron)
   {
      for (auto n : neuron.inputs)
      {
         os << n->id << "\t-->\t[" << neuron.id << "]\n";
      }
      for (auto n : neuron.outputs)
      {
         os << "[" << neuron.id << "]\t-->\t" << n->id << std::endl;
      }

      return os;
   }

   auto
   begin()
   {
      return this;
   }

   auto
   end()
   {
      return this + 1;
   }
};


struct NeuronLayer : Connectable< NeuronLayer >
{
   std::vector< Neuron > neurons;

   NeuronLayer(unsigned count)
   {
      while (count-- > 0)
      {
         neurons.emplace_back(Neuron{});
      }
   }

   friend std::ostream&
   operator<<(std::ostream& os, const NeuronLayer& layer)
   {
      for (auto n : layer.neurons)
      {
         os << n;
      }
      return os;
   }

   auto
   begin()
   {
      return neurons.begin();
   }

   auto
   end()
   {
      return neurons.end();
   }
};


int
main()
{
   Neuron n1, n2;
   NeuronLayer l1{2}, l2{3};
   n1.connect_to(l1);
   l1.connect_to(l2);
   l2.connect_to(n2);

   std::cout << l1 << std::endl;
   std::cout << l2 << std::endl;

   return 0;
}
