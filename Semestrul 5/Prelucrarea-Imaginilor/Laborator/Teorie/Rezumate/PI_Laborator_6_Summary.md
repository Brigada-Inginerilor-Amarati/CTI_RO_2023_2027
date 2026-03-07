# Laboratory 6: Attention Mechanisms

## 1. Introduction to Attention Mechanisms

**Attention mechanisms** are effective methods for improving the performance of neural networks.

Key properties:
- Initially proposed to enhance NLP models, later became one of the most effective methods for various machine learning tasks
- Neural networks with attention-based components can automatically distinguish the relative importance of features by assigning corresponding weights to achieve higher classification or regression accuracy
- The main idea stems from human perception: the ability to concentrate on an important part of information and ignore other information

---

## 2. Attention Mechanism Components

Attention mechanisms use three key components:

- **Query** (Volitional cue): The current focus or question
- **Keys** (Nonvolitional cues): Available information to match against
- **Values** (Sensory inputs): The actual data to be weighted

**Figure 1**: Attention mechanisms bias selection over values via attention pooling, which incorporates queries and keys.

The attention mechanism computes a weighted sum of values, where weights are determined by the compatibility between the query and keys.

---

## 3. Attention Pooling: Nadaraya-Watson Kernel Regression

### Overview

The **Nadaraya-Watson kernel regression** model is a simple example for demonstrating machine learning with attention mechanisms.

**Regression problem**: Given a dataset of input-output pairs {(x₁, y₁), ..., (xₙ, yₙ)}, how to learn f to predict the output ŷ = f(x) for any new input x?

### Basic Formula

Weigh the outputs yᵢ according to their input locations:

$$f(x) = \sum_{i=1}^{n} \frac{K(x - x_i)}{\sum_{j=1}^{n} K(x - x_j)} y_i, \qquad (1)$$

where K is a **kernel** function.

### Attention Formulation

Rewrite (1) as:

$$f(x) = \sum_{i=1}^{n} \alpha(x, x_i) y_i, \qquad (2)$$

where:
- x is the **query**
- (xᵢ, yᵢ) is the **key-value** pair
- α(x, xᵢ) is the **attention weight**

### Nonparametric Attention Pooling

Plugging the Gaussian kernel $K(u) = \frac{1}{\sqrt{2\pi}} \exp\left(-\frac{u^2}{2}\right)$ into (1) gives:

$$f(x) = \sum_{i=1}^{n} \text{softmax}\left(-\frac{1}{2}(x - x_i)^2\right) y_i. \qquad (3)$$

Equation (3) is an example of **nonparametric attention pooling**.

### Parametric Attention Pooling

Learnable parameters can be integrated into attention pooling. For example:

$$f(x) = \sum_{i=1}^{n} \text{softmax}\left(-\frac{1}{2}((x - x_i)\mathbf{w})^2\right) y_i. \qquad (4)$$

where **w** is a learnable parameter.

---

## 3.1 Nadaraya-Watson Kernel Regression in PyTorch

### Nonparametric Model

```python
n_train = 50  # No. of training examples
x_train, _ = torch.sort(torch.rand(n_train) * 5)  # Training inputs (keys)

def f(x):
    return 2 * torch.sin(x) + x**0.8

y_train = f(x_train) + torch.normal(0.0, 0.5, (n_train,))  # Training outputs
x_test = torch.arange(0, 5, 0.1)  # Testing examples (queries)
y_truth = f(x_test)  # Ground-truth outputs for the testing examples
n_test = len(x_test)  # No. of testing examples

x_repeat = x_test.repeat_interleave(n_train).reshape((-1, n_train))
attention_weights = F.softmax(-(x_repeat - x_train)**2 / 2, dim=1)
y_hat = torch.matmul(attention_weights, y_train)
```

### Parametric Model

```python
class NWKernelRegression(nn.Module):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.w = nn.Parameter(torch.rand((1,), requires_grad=True))

    def forward(self, queries, keys, values):
        queries = queries.repeat_interleave(keys.shape[1]).reshape((-1, keys.shape[1]))
        self.attention_weights = F.softmax(-((queries - keys) * self.w)**2 / 2, dim=1)
        return torch.bmm(self.attention_weights.unsqueeze(1),
                        values.unsqueeze(-1)).reshape(-1)

net = NWKernelRegression()
loss = nn.MSELoss(reduction='none')
optimizer = torch.optim.SGD(net.parameters(), lr=0.5)

train_loss_all = []
for epoch in range(5):
    optimizer.zero_grad()
    l = loss(net(x_train, keys, values), y_train)
    l.sum().backward()
    optimizer.step()
    print(f'epoch {epoch + 1}, loss {float(l.sum()):.6f}')
    train_loss_all.append(float(l.sum()))
```

---

## 4. Attention Scoring Functions

### General Formula

Suppose we have a query **q** ∈ ℝ^q and m key-value pairs (**k**₁, **v**₁), ..., (**k**ₘ, **v**ₘ), where **k**ᵢ ∈ ℝ^k and **v**ᵢ ∈ ℝ^v.

The attention pooling f is instantiated as a weighted sum of the values:

$$f(\mathbf{q}, (\mathbf{k}_1, \mathbf{v}_1), \ldots, (\mathbf{k}_m, \mathbf{v}_m)) = \sum_{i=1}^{m} \alpha(\mathbf{q}, \mathbf{k}_i) \mathbf{v}_i \in \mathbb{R}^v, \qquad (5)$$

where the attention weight (scalar) for the query **q** and key **k**ᵢ is computed by the softmax operation of an attention scoring function a that maps two vectors to a scalar:

$$\alpha(\mathbf{q}, \mathbf{k}_i) = \text{softmax}(a(\mathbf{q}, \mathbf{k}_i)) = \frac{\exp(a(\mathbf{q}, \mathbf{k}_i))}{\sum_{j=1}^{m} \exp(a(\mathbf{q}, \mathbf{k}_j))} \in \mathbb{R}. \qquad (6)$$

### Additive Attention

**Scoring function** → **additive attention** defined by:

$$a(\mathbf{q}, \mathbf{k}) = \mathbf{w}_v^T \tanh(\mathbf{W}_q \mathbf{q} + \mathbf{W}_k \mathbf{k}) \in \mathbb{R}, \qquad (7)$$

where the parameters **W**_q ∈ ℝ^(h×q), **W**_k ∈ ℝ^(h×k), **w**_v ∈ ℝ^h are learnable, and **q** ∈ ℝ^q, **k** ∈ ℝ^k are query and key.

### Scaled Dot-Product Attention

**Scoring function** → **scaled dot-product attention** defined by:

$$a(\mathbf{q}, \mathbf{k}) = \frac{\mathbf{q}^T \mathbf{k}}{\sqrt{d}}, \qquad (8)$$

where d is the length of query and key vectors.

---

## 4.1 Attention Scoring Functions in PyTorch

### Additive Attention

```python
class AdditiveAttention(nn.Module):
    """Additive attention."""
    def __init__(self, key_size, query_size, num_hiddens, dropout, **kwargs):
        super(AdditiveAttention, self).__init__(**kwargs)
        self.W_k = nn.Linear(key_size, num_hiddens, bias=False)
        self.W_q = nn.Linear(query_size, num_hiddens, bias=False)
        self.W_v = nn.Linear(num_hiddens, 1, bias=False)
        self.dropout = nn.Dropout(dropout)

    def forward(self, queries, keys, values, valid_lens):
        queries, keys = self.W_q(queries), self.W_k(keys)

        features = queries.unsqueeze(2) + keys.unsqueeze(1)
        features = torch.tanh(features)

        scores = self.W_v(features).squeeze(-1)
        self.attention_weights = masked_softmax(scores, valid_lens)

        return torch.bmm(self.dropout(self.attention_weights), values)
```

### Scaled Dot-Product Attention

```python
class DotProductAttention(nn.Module):
    """Scaled dot product attention."""
    def __init__(self, dropout, **kwargs):
        super(DotProductAttention, self).__init__(**kwargs)
        self.dropout = nn.Dropout(dropout)

    def forward(self, queries, keys, values, valid_lens=None):
        d = queries.shape[-1]
        scores = torch.bmm(queries, keys.transpose(1,2)) / math.sqrt(d)
        self.attention_weights = masked_softmax(scores, valid_lens)
        return torch.bmm(self.dropout(self.attention_weights), values)
```

---

## 5. Bahdanau Attention

### Overview

This attention mechanism is employed in the RNN encoder-decoder architecture studied in the context of machine translation.

The resulting attention model replaces the context variable **c** (the output of the encoder) with **c**_t' at any decoding time step t'.

### Formula

Suppose there are T tokens in the input sequence. The context variable at the decoding time step t' is the output of attention pooling:

$$\mathbf{c}_{t'} = \sum_{t=1}^{T} \alpha(\mathbf{s}_{t'-1}, \mathbf{h}_t) \mathbf{h}_t, \qquad (9)$$

where:
- The decoder hidden state **s**_t'-1 at time step t' − 1 is the query
- The encoder hidden states **h**_t are both the keys and values
- The attention weight α is computed as in (6), using the additive attention scoring function defined by (7)

---

## 5.1 Bahdanau Attention in PyTorch

```python
class Seq2SeqAttentionDecoder(AttentionDecoder):
    def __init__(self, vocab_size, embed_size, num_hiddens, num_layers,
                 dropout=0, **kwargs):
        super(Seq2SeqAttentionDecoder, self).__init__(**kwargs)
        self.attention = AdditiveAttention(
            num_hiddens, num_hiddens, num_hiddens, dropout)
        self.embedding = nn.Embedding(vocab_size, embed_size)
        self.rnn = nn.GRU(
            embed_size + num_hiddens, num_hiddens, num_layers,
            dropout=dropout)
        self.dense = nn.Linear(num_hiddens, vocab_size)

    def init_state(self, enc_outputs, enc_valid_lens, *args):
        outputs, hidden_state = enc_outputs
        return (outputs.permute(1, 0, 2), hidden_state, enc_valid_lens)

    def forward(self, X, state):
        enc_outputs, hidden_state, enc_valid_lens = state
        # The output `X` shape: (`num_steps`, `batch_size`, `embed_size`)
        X = self.embedding(X).permute(1, 0, 2)
        context = state[-1].repeat(X.shape[0], 1, 1)
        X_and_context = torch.cat((X, context), 2)
        output, state = self.rnn(X_and_context, state)
        output = self.dense(output).permute(1, 0, 2)
        return output, state
```

---

## 6. Multi-Head Attention

### Concept

- h projected queries, keys, and values are fed into attention pooling in parallel
- In the end, the h attention pooling outputs are concatenated and transformed with another learned linear projection, to produce the final output
- This design is called **multi-head attention**, where each of the h attention pooling outputs is a **head**
- Using fully-connected layers to perform learnable linear transformations, Figure 3 describes multi-head attention

### Mathematical Formulation

Mathematically, given a query **q** ∈ ℝ^d_q, a key **k** ∈ ℝ^d_k, and a value **v** ∈ ℝ^d_v, each attention head **h**ᵢ(i = 1, ..., h) is computed as:

$$\mathbf{h}_i = f(\mathbf{W}_i^{(q)} \mathbf{q}, \mathbf{W}_i^{(k)} \mathbf{k}, \mathbf{W}_i^{(v)} \mathbf{v}) \in \mathbb{R}^{p_v},$$

where the parameters **W**ᵢ^(q) ∈ ℝ^(p_q×d_q), **W**ᵢ^(k) ∈ ℝ^(p_k×d_k), and **W**ᵢ^(v) ∈ ℝ^(p_v×d_v) are learnable, and f is attention pooling, such as additive attention or scaled dot-product attention.

The multi-head attention output is another linear transformation via learnable parameters **W**_o ∈ ℝ^(p_o×hp_v) of the concatenation of the h heads:

$$\mathbf{W}_o \begin{bmatrix} \mathbf{h}_1 \\ \vdots \\ \mathbf{h}_h \end{bmatrix} \in \mathbb{R}^{p_o}.$$

---

## 6.1 Multi-Head Attention in PyTorch

p_o is specified via the argument `num_hiddens`.

```python
class MultiHeadAttention(nn.Module):
    """Multi-head attention."""
    def __init__(self, key_size, query_size, value_size, num_hiddens,
                 num_heads, dropout, bias=False, **kwargs):
        super(MultiHeadAttention, self).__init__(**kwargs)
        self.num_heads = num_heads
        self.attention = DotProductAttention(dropout)
        self.W_q = nn.Linear(query_size, num_hiddens, bias=bias)
        self.W_k = nn.Linear(key_size, num_hiddens, bias=bias)
        self.W_v = nn.Linear(value_size, num_hiddens, bias=bias)
        self.W_o = nn.Linear(num_hiddens, num_hiddens, bias=bias)

    def forward(self, queries, keys, values, valid_lens):
        # Shape of `queries`, `keys`, or `values` is:
        # (`batch_size`, no. of queries or key-value pairs, `num_hiddens`)
        # Shape of `valid_lens` is:
        # (`batch_size`,) or (`batch_size`, no. of queries)
        # After transposing, shape of output `queries`, `keys`, or `values` is:
        # (`batch_size` * `num_heads`, no. of queries or key-value pairs,
        # `num_hiddens` / `num_heads`)
        queries = transpose_qkv(self.W_q(queries), self.num_heads)
        keys = transpose_qkv(self.W_k(keys), self.num_heads)
        values = transpose_qkv(self.W_v(values), self.num_heads)

        if valid_lens is not None:
            valid_lens = torch.repeat_interleave(
                valid_lens, repeats=self.num_heads, dim=0)

        # Shape of `output` is: (`batch_size` * `num_heads`, no. of queries,
        # `num_hiddens` / `num_heads`)
        output = self.attention(queries, keys, values, valid_lens)

        # Shape of `output_concat` is:
        # (`batch_size`, no. of queries, `num_hiddens`)
        output_concat = transpose_output(output, self.num_heads)
        return self.W_o(output_concat)
```

---

## 7. Self-Attention and Positional Encoding

### Self-Attention (Intra-Attention)

Sequence encoding using self-attention and additional information for the sequence order.

**Self-attention** (intra-attention) → queries, keys and values are from the same source.

Given a sequence of input tokens **x**₁, ..., **x**_n, where any **x**ᵢ ∈ ℝ^d (1 ≤ i ≤ n), its self-attention outputs a sequence of the same length **y**₁, ..., **y**_n, where:

$$\mathbf{y}_i = f(\mathbf{x}_i, (\mathbf{x}_1, \mathbf{x}_1), \ldots, (\mathbf{x}_n, \mathbf{x}_n)) \in \mathbb{R}^d,$$

according to the definition of attention pooling f in (5).

### Positional Encoding

To use the sequence order information, we can inject absolute or relative positional information by adding **positional encoding** to the input representations.

Positional encodings can be either learned or fixed. In the following, we describe a fixed positional encoding based on sine and cosine functions.

Suppose that the input representation **X** ∈ ℝ^(n×d) contains d-dimensional embeddings for n tokens of a sequence.

The positional encoding outputs **X** + **P** using a positional embedding matrix **P** ∈ ℝ^(n×d) of the same shape, whose element on the ith row and the (2j)th or the (2j+1)th column is:

$$p_{i,2j} = \sin\left(\frac{i}{10000^{2j/d}}\right), \quad p_{i,2j+1} = \cos\left(\frac{i}{10000^{2j/d}}\right).$$

In the positional embedding matrix **P**, rows correspond to positions within a sequence and columns represent different positional encoding dimensions.

---

## 7.1 Self-Attention and Positional Encoding in PyTorch

### Positional Encoding

```python
class PositionalEncoding(nn.Module):
    """Positional encoding."""
    def __init__(self, num_hiddens, dropout, max_len=1000):
        super(PositionalEncoding, self).__init__()
        self.dropout = nn.Dropout(dropout)
        # Create a long enough `P`
        self.P = torch.zeros((1, max_len, num_hiddens))
        X = torch.arange(max_len, dtype=torch.float32).reshape(
            -1, 1) / torch.pow(10000, torch.arange(
            0, num_hiddens, 2, dtype=torch.float32) / num_hiddens)
        self.P[:, :, 0::2] = torch.sin(X)
        self.P[:, :, 1::2] = torch.cos(X)

    def forward(self, X):
        X = X + self.P[:, :X.shape[1], :].to(X.device)
        return self.dropout(X)
```

---

## 8. Transformer Model

### Architecture Overview

The **Transformer** model is solely based on attention mechanisms, without any convolutional or recurrent layer.

The Transformer is composed of an encoder and a decoder (Figure 4).

The input and output sequence embeddings are added with positional encoding, before being fed into the encoder and the decoder that stack modules based on self-attention.

### Encoder Structure

The Transformer encoder is a stack of multiple identical layers, where each layer has two sublayers:

1. **Multi-head self-attention pooling**
2. **Position-wise feed-forward network**

Specifically, in the encoder self-attention, queries, keys, and values are all from the outputs of the previous encoder layer.

Inspired by the ResNet design, a **residual connection** is employed around both sublayers.

### Decoder Structure

The Transformer decoder is also a stack of multiple identical layers with residual connections and layer normalizations.

Besides the two sublayers described in the encoder, the decoder inserts a third sublayer, known as the **encoder-decoder attention**, between these two.

In the encoder-decoder attention, queries are from the outputs of the previous decoder layer, and the keys and values are from the Transformer encoder outputs.

---

## 8.1 Transformer Model in PyTorch

### PositionWise FFN Sublayer

```python
class PositionWiseFFN(nn.Module):
    """Position-wise feed-forward network."""
    def __init__(self, ffn_num_input, ffn_num_hiddens, ffn_num_outputs,
                 **kwargs):
        super(PositionWiseFFN, self).__init__(**kwargs)
        self.dense1 = nn.Linear(ffn_num_input, ffn_num_hiddens)
        self.relu = nn.ReLU()
        self.dense2 = nn.Linear(ffn_num_hiddens, ffn_num_outputs)

    def forward(self, X):
        return self.dense2(self.relu(self.dense1(X)))
```

### Add & Norm Implementation

```python
class AddNorm(nn.Module):
    """Residual connection followed by layer normalization."""
    def __init__(self, normalized_shape, dropout, **kwargs):
        super(AddNorm, self).__init__(**kwargs)
        self.dropout = nn.Dropout(dropout)
        self.ln = nn.LayerNorm(normalized_shape)

    def forward(self, X, Y):
        return self.ln(self.dropout(Y) + X)
```

### EncoderBlock Class

EncoderBlock class contains two sublayers: multi-head self-attention and position-wise feed-forward networks.

```python
class EncoderBlock(nn.Module):
    """Transformer encoder block."""
    def __init__(self, key_size, query_size, value_size, num_hiddens,
                 norm_shape, ffn_num_input, ffn_num_hiddens, num_heads,
                 dropout, use_bias=False, **kwargs):
        super(EncoderBlock, self).__init__(**kwargs)
        self.attention = MultiHeadAttention(
            key_size, query_size, value_size, num_hiddens, num_heads, dropout,
            use_bias)
        self.addnorm1 = AddNorm(norm_shape, dropout)
        self.ffn = PositionWiseFFN(
            ffn_num_input, ffn_num_hiddens, num_hiddens)
        self.addnorm2 = AddNorm(norm_shape, dropout)

    def forward(self, X, valid_lens):
        Y = self.addnorm1(X, self.attention(X, X, X, valid_lens))
        return self.addnorm2(Y, self.ffn(Y))
```

### TransformerEncoder

TransformerEncoder → `num_layers` instances of the EncoderBlock class are stacked.

```python
class TransformerEncoder(Encoder):
    """Transformer encoder."""
    def __init__(self, vocab_size, key_size, query_size, value_size,
                 num_hiddens, norm_shape, ffn_num_input, ffn_num_hiddens,
                 num_heads, num_layers, dropout, use_bias=False, **kwargs):
        super(TransformerEncoder, self).__init__(**kwargs)
        self.num_hiddens = num_hiddens
        self.embedding = nn.Embedding(vocab_size, num_hiddens)
        self.pos_encoding = PositionalEncoding(num_hiddens, dropout)
        self.blks = nn.Sequential()
        for i in range(num_layers):
            self.blks.add_module("block"+str(i),
                EncoderBlock(key_size, query_size, value_size, num_hiddens,
                            norm_shape, ffn_num_input, ffn_num_hiddens,
                            num_heads, dropout, use_bias))

    def forward(self, X, valid_lens, *args):
        # Since positional encoding values are between -1 and 1, the embedding
        # values are multiplied by the square root of the embedding dimension
        # to rescale before they are summed up
        X = self.pos_encoding(self.embedding(X) * math.sqrt(self.num_hiddens))
        self.attention_weights = [None] * len(self.blks)
        for i, blk in enumerate(self.blks):
            X = blk(X, valid_lens)
            self.attention_weights[
                i] = blk.attention.attention.attention_weights
        return X
```

### DecoderBlock Implementation

```python
class DecoderBlock(nn.Module):
    # The `i`-th block in the decoder
    def __init__(self, key_size, query_size, value_size, num_hiddens,
                 norm_shape, ffn_num_input, ffn_num_hiddens, num_heads,
                 dropout, i, **kwargs):
        super(DecoderBlock, self).__init__(**kwargs)
        self.i = i
        self.attention1 = MultiHeadAttention(
            key_size, query_size, value_size, num_hiddens, num_heads, dropout)
        self.addnorm1 = AddNorm(norm_shape, dropout)
        self.attention2 = MultiHeadAttention(
            key_size, query_size, value_size, num_hiddens, num_heads, dropout)
        self.addnorm2 = AddNorm(norm_shape, dropout)
        self.ffn = PositionWiseFFN(ffn_num_input, ffn_num_hiddens,
                                   num_hiddens)
        self.addnorm3 = AddNorm(norm_shape, dropout)

    def forward(self, X, state):
        enc_outputs, enc_valid_lens = state[0], state[1]
        if state[2][self.i] is None:
            key_values = X
        else:
            key_values = torch.cat((state[2][self.i], X), axis=1)
        state[2][self.i] = key_values
        if self.training:
            batch_size, num_steps, _ = X.shape
            dec_valid_lens = torch.arange(
                1, num_steps + 1, device=X.device).repeat(batch_size, 1)
        else:
            dec_valid_lens = None

        # Self-attention
        X2 = self.attention1(X, key_values, key_values, dec_valid_lens)
        Y = self.addnorm1(X, X2)
        # Encoder-decoder attention weights
        Y2 = self.attention2(Y, enc_outputs, enc_outputs, enc_valid_lens)
        Z = self.addnorm2(Y, Y2)
        return self.addnorm3(Z, self.ffn(Z)), state
```

### TransformerDecoder

Transformer decoder composed of `num_layers` instances of DecoderBlock; a fully-connected layer computes the prediction for all the `vocab_size` possible output tokens.

```python
class TransformerDecoder(AttentionDecoder):
    def __init__(self, vocab_size, key_size, query_size, value_size,
                 num_hiddens, norm_shape, ffn_num_input, ffn_num_hiddens,
                 num_heads, num_layers, dropout, **kwargs):
        super(TransformerDecoder, self).__init__(**kwargs)
        self.num_hiddens = num_hiddens
        self.num_layers = num_layers
        self.embedding = nn.Embedding(vocab_size, num_hiddens)
        self.pos_encoding = PositionalEncoding(num_hiddens, dropout)
        self.blks = nn.Sequential()
        for i in range(num_layers):
            self.blks.add_module("block"+str(i),
                DecoderBlock(key_size, query_size, value_size, num_hiddens,
                            norm_shape, ffn_num_input, ffn_num_hiddens,
                            num_heads, dropout, i))
        self.dense = nn.Linear(num_hiddens, vocab_size)

    def init_state(self, enc_outputs, enc_valid_lens, *args):
        return [enc_outputs, enc_valid_lens, [None] * self.num_layers]

    def forward(self, X, state):
        X = self.pos_encoding(self.embedding(X) * math.sqrt(self.num_hiddens))
        self._attention_weights = [[None] * len(self.blks) for _ in range(2)]
        for i, blk in enumerate(self.blks):
            X, state = blk(X, state)
            # Decoder self-attention weights
            self._attention_weights[0][
                i] = blk.attention1.attention.attention_weights
            # Encoder-decoder attention weights
            self._attention_weights[1][
                i] = blk.attention2.attention.attention_weights
        return self.dense(X), state
```

---

## Summary

This laboratory covered comprehensive concepts related to Attention Mechanisms:

1. **Introduction**: Understanding attention as a method to focus on important information
2. **Attention Components**: Query, Keys, and Values framework
3. **Nadaraya-Watson Kernel Regression**: Simple nonparametric and parametric attention models
4. **Attention Scoring Functions**: Additive attention and scaled dot-product attention
5. **Bahdanau Attention**: Attention mechanism for RNN encoder-decoder architecture
6. **Multi-Head Attention**: Parallel attention pooling with multiple heads
7. **Self-Attention and Positional Encoding**: Intra-attention with sequence position information
8. **Transformer Model**: Complete encoder-decoder architecture based solely on attention mechanisms

All implementations use PyTorch with practical examples for regression tasks and machine translation.
