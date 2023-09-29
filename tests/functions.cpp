#include "CaberNet/CaberNet.h"
#include <gtest/gtest.h>

TEST(functions, gradient) {
    /*
    import torch.nn.functional as F

    # Initialize tensors
    x = torch.tensor([[1, 2, 3], [4, 5, 6]], dtype=torch.float32, requires_grad=False)
    w = torch.tensor([[1, 2, -3], [4, 5, 6], [7, 8, -9], [10, 11, -12]], dtype=torch.float32, requires_grad=True)
    b = torch.tensor([1, 2, 3, 4], dtype=torch.float32, requires_grad=True)
    I = torch.tensor([[1,1,1,1],[1,1,1,1]], dtype=torch.float32)

    # Perform linear operation using torch.nn.functional.linear
    x = F.linear(x, w, b)
    x = F.relu(x)
    x.backward(I)

    # Print the result
    print(x)
    print(w.grad)
    print(b.grad)

    */
    net::Tensor x({2,3}, false); x.fill({1,2,3,4,5,6});
    net::Tensor w({4,3}, true); w.fill({1,2,-3,4,5,6,7,8,-9,10,11,-12});
    net::Tensor b({1,4}, true); b.fill({1,2,3,4});
    net::Tensor I({2,4}, false); I.fill(1);

    x = net::function::linear(x,w,b);
    x = net::function::relu(x);
    x.perform();
    x.backward(I);

    /*
    Results should be:
    [0, 34, 0, 0, 0, 79, 17, 27, ]
    [0, 0, 0, 5, 7, 9, 4, 5, 6, 4, 5, 6, ]
    [0, 2, 1, 1, ]
    */
    ASSERT_EQ([0, 34, 0, 0, 0, 79, 17, 27], x);
    ASSERT_EQ([0, 0, 0, 5, 7, 9, 4, 5, 6, 4, 5, 6], w.gradient());
    ASSERT_EQ([0, 2, 1, 1], b.gradient());
}
